/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_dimensions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 19:38:28 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/26 11:35:02 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "errors.h"
#include "info.h"
#include "ft_strlen.h"

#include <stdio.h>
/*transpose the map from chars to the 2D int array in info*/
static int	record_dimensions(t_info *info, char **map, int i, int j)
{
	int	mapstart;

	mapstart = info->mapstart;
	if (!map[mapstart + i][j])
	{
		while (j < info->map_width)
		{
			info->map[i][j] = 2;
			j++;
		}
	}
	else if (map[mapstart + i][j] == ' ')
		info->map[i][j] = 2;
	else if (map[mapstart + i][j] == '0')
		info->map[i][j] = 0;
	else if (map[mapstart + i][j] == '1')
		info->map[i][j] = 1;
	return (j);
}

/*cycle through the provided map to so that record_dimensions can
transpose it into info*/
void	set_dimensions(t_info *info, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < info->map_height)
	{
		while (j <= info->map_width)
		{
			j = record_dimensions(info, map, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

/*find the maximum dimensions of the map, so that they can
be filled later*/
void	get_dimensions(t_info *info, char **map, int mapstart)
{
	int	len;
	int	i;

	i = mapstart + 1;
	len = ft_strlen(map[mapstart]);
	while (map[i])
	{
		if (len < ft_strlen(map[i]))
			len = ft_strlen(map[i]);
		i++;
	}
	info->map_width = len;
	info->map_height = i - mapstart;
	i = 0;
	info->map = malloc(sizeof(int *) * info->map_height);
	if (!info->map)
		malloc_error("get dimensions Y value");
	while (i < info->map_height)
	{
		info->map[i] = malloc(sizeof(int) * info->map_width);
		if (!info->map[i])
			malloc_error("get_dimensions X value");
		i++;
	}
}
