/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:07:32 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 21:03:26 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "errors.h"
#include "file_checker.h"
#include "info.h"
#include "initialize.h"


#include <stdio.h>

/*set the info struct to null in case of 
memory fuckery*/
static void	set_null(t_info *info)
{
	info->floor_color = 0;
	info->ceiling_color = 0;
	info->north_texture = 0;
	info->east_texture = NULL;
	info->south_texture = NULL;
	info->west_texture = NULL;
	info->player_direction = 0;
	info->player_x = 0;
	info->player_y = 0;
	info->map_width = 0;
	info->map_height = 0;
	info->map = NULL;
}

void	free_info(t_info *info)
{
	free(info->north_texture);
	free(info->east_texture);
	free(info->south_texture);
	free(info->west_texture);
	free(info);
}

/*initialize the struct to null, then do some basic checks
before filling the info struct*/
t_info	*parse_input(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		malloc_error("initialize_info");
	set_null(info);
	check_file(argv[argc - 1]);
	initialize_info(info, argv[1]);
	return (info);
}
