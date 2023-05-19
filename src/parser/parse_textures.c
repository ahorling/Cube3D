/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:27:43 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 21:57:22 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "colours.h"
#include "errors.h"
#include "info.h"
#include "file_checker.h"
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

static void	check_textures(char **strings)
{
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

static int	get_colour(char **strings, char *id)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	while (strings[i])
	{
		if (ft_strncmp(id, strings[i], 2) == 0)
			break;
		i++;
	}
	r = get_code(strings[i], 0);
	g = get_code(strings[i], 1);
	b = get_code(strings[i], 2);
	i = assemble_colour(r, g, b);
	exit(0);
}

char	**get_textures(char **strings, t_info *info)
{
	check_textures(strings);
	info->north_texture = find_texture(strings, "NO ");
	info->east_texture = find_texture(strings, "EA ");
	info->south_texture = find_texture(strings, "SO ");
	info->west_texture = find_texture(strings, "WE ");
	info->floor_color = get_colour(strings, "F ");
	// info->ceiling_color = get_colout(strings, "C ");
	exit (0);
}