/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:07:32 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 17:27:30 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "file_checker.h"
#include "info.h"
#include "initialize.h"

#include <unistd.h>
#include <stdio.h>

t_info	*parse_input(int argc, char **argv)
{
	t_info	*info;

	check_file(argv[argc - 1]);
	info = initialize_info(argv[1]);
	return (info);
}
