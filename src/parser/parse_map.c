/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 21:05:00 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 16:47:40 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stdbool.h"
#include "errors.h"
#include "find_map.h"
#include "ft_strlen.h"
#include "info.h"


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static char	**find_player(t_info *info, char **map, int start)
{
	int i;
	int	j;
	int	count;

	i = start;
	j = 0;
	count = 0;
	while(map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
				|| map[i][j] == 'W')
				{
					info->player_direction = map[i][j];
					info->player_x = j;
					info->player_y = i - start;
					map[i][j] = '0';
					count++;
					j++;
				}
			if (count > 1)
				map_error(2);
			j++;
		}
		j = 0;
		i++;
	}
	if (count == 0)
		map_error(3);
	return (map);
}

static bool	check_valid(char **map, int i, int j)
{
	bool	valid;
	int		x;
	int		y;

	x = j - 1;
	y = i - 1;
	valid = true;

	if (x == -1)
	{
		valid = false;
		return (valid);
	}
	while (y <= i + 1)
	{
		while (x <= j + 1)
		{
			if (!map[y][x] || (map[y][x] != '0' && map[y][x] != '1'))
			{
				valid = false;
				return (valid);
			}
			x++;
		}
		x = j - 1;
		y++;
	}
	return (valid);
}

void	verify_map(char **map, int mapstart)
{
	int	j;
	int i;

	i = mapstart;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '0')
				if (check_valid(map, i, j) == false)
				{
					printf("Invalid map point at %c, at position x: %d, y: %d\n", map[i][j], j + 1, i + 1 - mapstart);
					map_error(4);
				}
			j++;
		}
		j = 0;
		i++;
	}
}

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
	// printf("info->height = %d\n", info->map_height);
	if	(!info->map)
		malloc_error("get dimensions Y value");
	while (i <= info->map_height)
	{
		info->map[i] = malloc(sizeof(int) * info->map_width);
		if (!info->map[i])
			malloc_error("get_dimensions X value");
		i++;
		// printf("info->width = %d\n", info->map_width);
	}
	// printf("Map has dimensions of x: %d, y: %d\n", info->map_width, info->map_height);
}

void	set_dimensions(t_info *info, char **map, int mapstart)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < info->map_height)
	{
		while (j <= info->map_width)
		{
			if (!map[mapstart + i][j])
			{
				while (j <= info->map_width)
				{
					info->map[i][j] = 2;
					j++;
				}
			}
			else if (map[mapstart + i][j] == ' ')
				info->map[i][j] = -1;
			else if (map[mapstart + i][j] == '0')
				info->map[i][j] = 0;
			else if (map[mapstart + i][j] == '1')
				info->map[i][j] = 1;
			j++;
		}
		j = 0;
		i++;
	}
}

void	get_map(t_info *info, char **filecontents)
{
	int	mapstart;
	int x = 0;
	int y = 0;

	mapstart = find_map(filecontents);
	filecontents = find_player(info, filecontents, mapstart);
	verify_map(filecontents, mapstart);
	get_dimensions(info, filecontents, mapstart);
	set_dimensions(info, filecontents, mapstart);
	// while (y < info->map_height)
	// {
	// 	while (x <= info->map_width)
	// 	{
	// 		printf("%d", info->map[y][x]);
	// 		x++;
	// 	}
	// 	printf("\n");
	// 	x = 0;
	// 	y++;
	// }
	// // printf("player is located at x: %d, y: %d\n", info->player_x, info->player_y);
}