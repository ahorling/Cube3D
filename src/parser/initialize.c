/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 20:15:36 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/18 21:35:23 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "errors.h"
#include "info.h"
#include "get_lines.h"

t_info	*initialize_info(char *path)
{
	t_info	*info;
	char	**lines;

	info = malloc(sizeof(info));
	if (!info)
		malloc_error("initialize_info");
	lines = get_lines(path);
	exit(0);
}