/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 21:05:00 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/22 22:16:03 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stdbool.h"
#include "errors.h"
#include "find_map.h"
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
					map[i][j] = 0;
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

static bool	verify_map(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 0)
				check_valid(0, 1);
			exit(0);			
		}
	}
}

void	get_map(t_info *info, char **filecontents)
{
	int	mapstart;

	mapstart = find_map(filecontents);
	filecontents = find_player(info, filecontents, mapstart);
	printf("Player is facing direction %c, at position x: %d, y: %d\n", info->player_direction, info->player_x, info->player_y);
	verify_map(filecontents, mapstart);

}