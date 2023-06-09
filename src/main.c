/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 16:19:23 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/25 19:51:36 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "errors.h"
#include "info.h"
#include "parser.h"

// void	leaks(void)
// {
// 	system("leaks -q cub3D");
// }

// atexit(leaks);
int	main(int argc, char **argv)
{
	t_info	*info;

	info = NULL;
	if (argc != 2)
		argument_error();
	info = parse_input(argc, argv);
	cub3d(info);
	free_info(info);
	exit(EXIT_SUCCESS);
}
