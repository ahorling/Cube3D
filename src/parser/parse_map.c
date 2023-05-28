/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 21:05:00 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/28 11:44:49 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stdbool.h"
#include "errors.h"
#include "find_map.h"
#include "ft_strlen.h"
#include "info.h"
#include "map_dimensions.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*record the relevant player information in the info struct*/
static int	record_player(t_info *info, char **map, int i, int j)
{
	int	start;

	start = info->mapstart;
	info->player_direction = map[i][j];
	info->player_x = j;
	info->player_y = i - start;
	j++;
	return (j);
}

/*cycle through the map to find the player identifier and record it*/
static void	find_player(t_info *info, char **map, int start)
{
	int	i;
	int	j;
	int	count;

	i = start;
	j = 0;
	count = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
				|| map[i][j] == 'W')
			{
				j = record_player(info, map, i, j);
				map[i][j - 1] = '0';
				count++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (count == 0 || count > 1)
		map_error(2);
}

/*compare the current char with all chars around it to 
make sure that it is a playable space*/
static bool	check_valid(char **map, int i, int j)
{
	int		x;
	int		y;

	x = j - 1;
	y = i - 1;
	if (x == -1)
		return (false);
	while (y <= i + 1)
	{
		if (!map[y])
			return (false);
		while (x <= j + 1)
		{
			if (!map[y][x] || (map[y][x] != '0' && map[y][x] != '1'))
				return (false);
			x++;
		}
		x = j - 1;
		y++;
	}
	return (true);
}

/*verify that the map is, actually, a playable map!*/
void	verify_map(char **map, int mapstart)
{
	int	j;
	int	i;

	i = mapstart;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '0')
				if (check_valid(map, i, j) == false)
					map_error(4);
			j++;
		}
		j = 0;
		i++;
	}
}

/*fill the info struct with the map and associated values*/
void	get_map(t_info *info, char **filecontents)
{
	int	mapstart;
	int	i;

	i = 0;
	mapstart = info->mapstart;
	find_player(info, filecontents, mapstart);
	verify_map(filecontents, mapstart);
	get_dimensions(info, filecontents, mapstart);
	set_dimensions(info, filecontents);
	while (filecontents[i])
	{
		free(filecontents[i]);
		i++;
	}
}
