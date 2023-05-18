/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:40:31 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/18 17:48:23 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	stop(char *str)
{
	if (str)
	{
		write(STDERR_FILENO, "cub3d: ", 7);
		perror(str);
	}
	else
		perror("cub3d: ");
	exit(EXIT_FAILURE);
}
