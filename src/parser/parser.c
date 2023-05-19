/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:07:32 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 19:33:10 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "file_checker.h"
#include "info.h"
#include "initialize.h"

#include <unistd.h>

t_info	*parse_input(int argc, char **argv)
{
	t_info	*info;

	check_file(argv[1]);
	info = initialize_info(argv[1]);
	return (NULL);
}
