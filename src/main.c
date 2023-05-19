/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 16:19:23 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/18 18:36:06 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "errors.h"
#include "info.h"

int	main(int argc, char **argv)
{
	t_info *info;

	info = NULL;
	if (argc != 2)
		argument_error();
	info = parse_input(argc, argv);
	// cubed();
	exit(0);
}