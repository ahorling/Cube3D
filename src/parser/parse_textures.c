/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:27:43 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 17:25:33 by fholwerd      ########   odam.nl         */
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
			break;
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

static void	check_garbage(char **strings, int map_start)
{
	int		i;
	bool	garbage;

	i = 0;
	garbage = false;
	while (strings[i] && i < map_start)
	{
		while (!strings[i][0])
			i++;
		if (i >= map_start)
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

static void	check_textures(char **strings)
{
	int	map_start;

	map_start = find_map(strings);
	if (map_start == -1)
		map_error(1);
	printf("map starts on line: %d\n", map_start);
	check_garbage(strings, map_start);
	if (check_duplicates(strings, "NO", 2) == true)
		texture_error(4);
	if (check_duplicates(strings, "EA", 2) == true)
		texture_error(4);
	if (check_duplicates(strings, "SO", 2) == true)
		texture_error(4);
	if (check_duplicates(strings, "WE", 2) == true)
		texture_error(4);
	if (check_duplicates(strings, "F", 1) == true)
		texture_error(4);
	if (check_duplicates(strings, "C", 1) == true)
		texture_error(4);
}

void	get_textures(char **strings, t_info *info)
{
	check_textures(strings);
	info->north_texture = find_texture(strings, "NO ");
	info->east_texture = find_texture(strings, "EA ");
	info->south_texture = find_texture(strings, "SO ");
	info->west_texture = find_texture(strings, "WE ");
	info->floor_color = get_colour(strings, "F ");
	printf("floor colour: %x\n", info->floor_color);
	info->ceiling_color = get_colour(strings, "C ");
}