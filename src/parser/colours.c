/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colours.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 21:30:08 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 19:24:30 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "errors.h"
#include "ft_atoi.h"
#include "ft_substr.h"
#include "ft_strncmp.h"

/*Checks to see if the provided colour scheme is valid*/
void	colour_checker(char *string)
{
	int	i;
	int	count;

	i = 2;
	count = 0;
	while (string[i])
	{
		if (string[i] == ',')
			count++;
		if ((string[i] < '0' || string[i] > '9') && string[i] != ',')
		{
			colour_error(1);
		}
		i++;
	}
	if (count != 2)
		colour_error(1);
}

/*Convert three ints into a single hex code*/
int	assemble_colour(int r, int g, int b)
{
	int	hex;

	hex = ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + (0xff);
	return (hex);
}

/*Grab 3 ints from the provided rgb code*/
int	get_code(char *string, int skip)
{
	int		start;
	int		end;
	int		ret;
	char	*temp;

	start = 2;
	end = start;
	while (string[end] != ',' && string[end])
	{
		end++;
		if (string[end] == ',' && skip > 0)
		{
			end++;
			start = end;
			skip--;
		}
	}
	temp = ft_substr(string, start, end - start);
	ret = (int)ft_atoi(temp);
	if (ret > 255)
		colour_error(3);
	free(temp);
	return (ret);
}

/*find, check and convert the provided RGB value into a usable single hex*/
int	get_colour(char **strings, char *id)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	while (strings[i])
	{
		if (ft_strncmp(id, strings[i], 2) == 0)
			break ;
		i++;
	}
	if (strings[i] == '\0')
		colour_error(3);
	colour_checker(strings[i]);
	r = get_code(strings[i], 0);
	g = get_code(strings[i], 1);
	b = get_code(strings[i], 2);
	i = assemble_colour(r, g, b);
	return (i);
}
