/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:27:43 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/28 11:59:49 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "colours.h"
#include "errors.h"
#include "info.h"
#include "file_checker.h"
#include "find_map.h"
#include "ft_substr.h"
#include "ft_strcmp.h"
#include "ft_strlen.h"
#include "ft_strncmp.h"
#include "ft_strrchr.h"

#include <stdlib.h>
#include <stdio.h>

/*find the texture file associated with the given identifier*/
static char	*find_texture(char **strings, char *id)
{
	int		start;
	int		i;
	char	*texture_path;
	char	*temp;

	i = 0;
	while (strings[i])
	{
		if (ft_strncmp(id, strings[i], 3) == 0)
			break ;
		i++;
	}
	if (strings[i] == '\0')
		texture_error(1);
	texture_path = ft_substr(strings[i], 3, ft_strlen(strings[i]));
	if (check_dots(texture_path) == 1)
		texture_error(2);
	temp = ft_strrchr(texture_path, '.');
	start = ft_strcmp(".png", temp);
	if (start != 0)
		texture_error(3);
	return (texture_path);
}

/*check if there are more than one identifiers for textures*/
static bool	check_duplicates(char **strings, char *id, int len)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (strings[i])
	{
		if (ft_strncmp(id, strings[i], len) == 0)
			count++;
		i++;
	}
	if (count == 0)
		texture_error(1);
	if (count > 1)
		return (true);
	return (false);
}

/*check to see if there is any non-authorized values in the file*/
static void	check_garbage(char **strings, t_info *info)
{
	int		i;
	bool	garbage;

	i = 0;
	garbage = false;
	while (strings[i] && i < info->mapstart)
	{
		while (!strings[i][0])
			i++;
		if (i >= info->mapstart)
			break ;
		if (ft_strncmp(strings[i], "NO ", 3) != 0 \
			&& ft_strncmp(strings[i], "EA ", 3) != 0 \
			&& ft_strncmp(strings[i], "SO ", 3) != 0 \
			&& ft_strncmp(strings[i], "WE ", 3) != 0 \
			&& ft_strncmp(strings[i], "F ", 2) != 0 \
			&& ft_strncmp(strings[i], "C ", 2) != 0)
			garbage = true;
		i++;
	}
	if (garbage == true)
		file_error(1);
}

/*find the start of the map, and then check to make sure the
rest of the file follows the proper directions*/
static void	check_textures(t_info *info, char **strings)
{
	info->mapstart = find_map(strings);
	if (info->mapstart == -1)
		map_error(1);
	check_garbage(strings, info);
	if (check_duplicates(strings, "NO ", 3) == true)
		texture_error(4);
	if (check_duplicates(strings, "EA ", 3) == true)
		texture_error(4);
	if (check_duplicates(strings, "SO ", 3) == true)
		texture_error(4);
	if (check_duplicates(strings, "WE ", 3) == true)
		texture_error(4);
	if (check_duplicates(strings, "F ", 2) == true)
		texture_error(4);
	if (check_duplicates(strings, "C ", 2) == true)
		texture_error(4);
}

/*fill the info struct with the correct texture information*/
void	get_textures(char **strings, t_info *info)
{
	check_textures(info, strings);
	info->north_texture = find_texture(strings, "NO ");
	info->east_texture = find_texture(strings, "EA ");
	info->south_texture = find_texture(strings, "SO ");
	info->west_texture = find_texture(strings, "WE ");
	info->floor_color = get_colour(strings, "F ");
	info->ceiling_color = get_colour(strings, "C ");
}
