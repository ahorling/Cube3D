/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 19:25:13 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 20:13:16 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "errors.h"

void	map_error(int error)
{
	if (error == 1)
	{
		write(ERROR, "Map not provided or not last in the file\n", 41);
		exit(30);
	}
	if (error == 2)
	{
		write(ERROR, "Map has invalid number of player identifiers\n", 45);
		exit(31);
	}
	if (error == 4)
	{
		write(ERROR, "Provided map has invalid play area\n", 35);
		exit(32);
	}
}

void	file_error(int error)
{
	if (error == 1)
	{
		write(ERROR, "Found garbage in .cub file. Only include a valid", 49);
		write(ERROR, " map and the correct texture/colour flags\n", 42);
		exit(8);
	}
}

void	colour_error(int error)
{
	if (error == 1)
	{
		write(ERROR, "Invalid setup of colour scheme\n", 31);
		exit(24);
	}
	if (error == 2)
	{
		write(ERROR, "Invalid r, g or b value. values must be equal ", 47);
		write(ERROR, "to or greater than 0, and less than 256\n", 41);
		exit(25);
	}
	if (error == 3)
	{
		write(ERROR, "No valid floor or ceiling identifier\n", 37);
		exit(26);
	}
}
