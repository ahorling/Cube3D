/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:11:06 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 19:30:27 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "errors.h"
#include "info.h"
#include "find_map.h"
#include "ft_instring.h"

#include <stdio.h>
#include <unistd.h>

bool	valid_line(char *string)
{
	int	i;

	i = 0;
	if (string[i] == 0)
		return (false);
	while (ft_instring(string[i], VALID_MAP_CHAR) == true)
		i++;
	if (!string[i])
		return (true);
	return (false);
}

static int	possible_start(char **strings, int start)
{
	int	i;

	i = start;
	while (strings[i] && ft_instring(strings[i][0], VALID_MAP_CHAR) == false)
		i++;
	if (!strings[i])
		map_error(1);
	return (i);
}

int	find_map(char **strings)
{
	int	i;
	int	start;

	i = possible_start(strings, 0);
	start = i;
	while (strings)
	{
		while (strings[i] && valid_line(strings[i]) == true)
			i++;
		if (strings[i] == NULL)
			return (start);
		i++;
		i = possible_start(strings, i);
		start = i;
	}
	return (-1);
}
