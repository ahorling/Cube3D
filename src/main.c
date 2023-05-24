/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 16:19:23 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/24 18:55:55 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "errors.h"
#include "info.h"
#include "parser.h"


#include <stdio.h>
int	main(int argc, char **argv)
{
	t_info *info;

	info = NULL;
	if (argc != 2)
		argument_error();
	info = parse_input(argc, argv);
	printf("PARSING DONE: %x\n", info->floor_color);
	cub3d(info);
	free_info(info);
	exit(0);
}