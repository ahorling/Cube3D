/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 20:11:43 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/24 17:35:23 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "correct_color.h"
#include "deg_to_rad.h"
#include "draw_line.h"
#include "draw_rectangle.h"
#include "draw_walls.h"
#include "image_to_window.h"
#include "info.h"
#include "init_image.h"
#include "load_texture.h"
#include "minimap.h"
#include "movement.h"
#include "MLX42.h"
#include "point.h"
#include "put_pixel.h"
#include "raycaster.h"
#include "rectangle.h"
#include "stop.h"

void	free_map(t_raycaster rc, int **map)
{
	int	i;

	i = 0;
	while (i < rc.map_height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static t_raycaster	init_raycaster(t_info *info)
{
	t_raycaster	rc;

	printf("1: %x\n", info->floor_color);
	rc.floor_color = info->floor_color;
	printf("2\n");
	rc.ceiling_color = info->ceiling_color;
	rc.screen_width = 1600;
	rc.screen_height = 900;
	rc.map_width = info->map_width;
	rc.map_height = info->map_height;
	printf("testMAP\n");
	rc.map = info->map;
	printf("testAFTER\n");
	rc.tile_size = rc.screen_height / (rc.map_height * 3);
	rc.cpx = 0;
	rc.cpy = 0.66;
	printf("testPlayerPos\n");
	rc.px = (double)info->player_x;
	rc.py = (double)info->player_y;
	printf("testAFTER\n");
	rc.pdx = 1;
	rc.pdy = 0;
	rc.rdx = 0;
	rc.rdy = 0;
	rc.mspeed = 0.04999;
	rc.rspeed = 0.05;
	rc.pitch = 0;
	rc.mlx = mlx_init(rc.screen_width, rc.screen_height, "cub3D", true);
	if (!rc.mlx)
		stop("Failed to initialize mlx");
	rotate_player(&rc, deg_to_rad(-90));
	return (rc);
}

// Sets the background layer for floor and ceiling.
void	set_background(t_raycaster rc)
{
	draw_rect(rc.background,
		rect(0, 0, rc.screen_width, rc.screen_height / 2 + rc.pitch),
		rc.ceiling_color);
	draw_rect(rc.background,
		rect(0, rc.screen_height / 2 + rc.pitch,
			rc.screen_width, rc.screen_height / 2 - rc.pitch),
		rc.floor_color);
}

void	game_loop(void *param)
{
	t_raycaster	*rc;

	rc = param;
	movement(rc);
	raycast(rc);
	draw_map(*rc);
	printf("delta time: %f\n", rc->mlx->delta_time);
}

int	cub3d(t_info *info)
{
	t_raycaster	rc;

	printf("test1\n");
	rc = init_raycaster(info);
	printf("test2\n");
	rc.textures[0] = load_texture("robe_of_agony.png");
	rc.textures[1] = load_texture("stone.png");
	rc.textures[2] = load_texture("stone_bricks.png");
	rc.textures[3] = load_texture("wt_logo.png");
	printf("test3\n");
	rc.background = init_image(rc.mlx, rc.screen_width, rc.screen_height);
	rc.screen = init_image(rc.mlx, rc.screen_width, rc.screen_height);
	printf("test4\n");
	set_background(rc);
	printf("test5\n");
	raycast(&rc);
	printf("test6\n");
	draw_map(rc);
	printf("test7\n");
	image_to_window(rc.mlx, rc.background, 0, 0);
	image_to_window(rc.mlx, rc.screen, 0, 0);
	printf("test8\n");
	mlx_loop_hook(rc.mlx, game_loop, &rc);
	mlx_loop(rc.mlx);
	mlx_terminate(rc.mlx);
	free_map(rc, rc.map);
	system("leaks -q cub3D");
	return (EXIT_SUCCESS);
}
