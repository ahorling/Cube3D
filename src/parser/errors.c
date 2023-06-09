/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 16:59:12 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 22:13:09 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "errors.h"
#include "ft_strlen.h"
#include "ft_strrchr.h"
#include "info.h"

void	texture_error(int error)
{
	write(ERROR, "Error\n", 6);
	if (error == 1)
	{
		write(ERROR, "One or more texture file ", 26);
		write(ERROR, "identifiers missing from .cub file\n", 35);
		exit(20);
	}
	if (error == 2)
	{
		write(ERROR, "One of more texture files", 25);
		write(ERROR, " do not have a file extension.\n", 31);
		exit(21);
	}
	if (error == 3)
	{
		write(ERROR, "One or more texture files have ", 31);
		write(ERROR, " an incorrect file extension.\n", 30);
		exit(22);
	}
	if (error == 4)
	{
		write(ERROR, "Map file contains more than one identifier ", 44);
		write(ERROR, "for the same colour and/or textures.\n", 37);
		exit(23);
	}
}

void	argument_error(void)
{
	write(ERROR, "Error\n", 6);
	write(ERROR, "Invalid number of arguments. ", 30);
	write(ERROR, "Please make sure you are running the program in the ", 53);
	write(ERROR, "following way: ./cub3D [a file ending in .cub]\n", 47);
	exit(1);
}

void	read_error(void)
{
	write(ERROR, "Error\n", 6);
	write(ERROR, "Failed to read from file\n", 26);
	exit(6);
}

void	file_path_error(int error)
{
	write(ERROR, "Error\n", 6);
	if (error == -1)
	{
		write(ERROR, "Provided file does not have a file extension.\n", 46);
		exit(2);
	}
	if (error == 1)
	{
		write(ERROR, "Provided file has an incorrect file extension. ", 48);
		write(ERROR, "Please make sure you are providing a .cub file.\n", 48);
		exit(3);
	}
	if (error == 2)
	{
		write(ERROR, "Failure to open provided file.\n", 31);
		exit(4);
	}
	if (error == 3)
	{
		write(ERROR, "Provided .cub file has no contents\n", 35);
		exit(5);
	}
}

void	malloc_error(char *string)
{
	int	i;

	i = ft_strlen(string);
	write(ERROR, "Error\n", 6);
	write(ERROR, "Memory allocation failure occured in function: ", 48);
	write(ERROR, &string, i);
	write(ERROR, "\n", 1);
	exit(10);
}
