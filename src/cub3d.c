/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 20:11:43 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/23 15:44:40 by fholwerd      ########   odam.nl         */
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

int MAPX = 24;
int MAPY = 24;

// int worldMap[8][8]=
// {
// 	{1,1,1,1,1,1,1,1},
// 	{1,0,1,0,0,0,0,1},
// 	{1,0,1,0,0,0,0,1},
// 	{1,0,1,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,1,0,1},
// 	{1,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1}
// };

int worldMap[24][24]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	**convert_worldmap(void)
{
	int	**map;
	int	i;
	int	j;

	map = malloc(sizeof(int *) * MAPX);
	if (!map)
		return (NULL);
	i = 0;
	while (i < MAPX)
	{
		map[i] = malloc(sizeof(int) * MAPY);
		if (!map[i])
			return (NULL);
		j = 0;
		while (j < MAPY)
		{
			map[i][j] = worldMap[i][j];
			j++;
		}
		i++;
	}
	return (map);
}

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

static t_raycaster	init_raycaster(void)
{
	t_raycaster	rc;

	rc.floor_color = DARKGRAY;
	rc.ceiling_color = SKYBLUE;
	rc.screen_width = 1600;
	rc.screen_height = 900;
	rc.map_width = MAPX;
	rc.map_height = MAPY;
	rc.map = convert_worldmap();
	rc.tile_size = rc.screen_height / (rc.map_height * 3);
	rc.cpx = 0;
	rc.cpy = 0.66;
	rc.px = 4;
	rc.py = 2;
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

int	main(int argc, char *argv[])
{
	t_raycaster	rc;

	(void)argc;
	(void)argv;
	rc = init_raycaster();
	rc.textures[0] = load_texture("robe_of_agony.png");
	printf("%d\n", rc.textures[0]->height);
	printf("%d\n", rc.textures[0]->width);
	rc.textures[1] = load_texture("stone.png");
	rc.textures[2] = load_texture("stone_bricks.png");
	rc.textures[3] = load_texture("wt_logo.png");
	rc.background = init_image(rc.mlx, rc.screen_width, rc.screen_height);
	rc.screen = init_image(rc.mlx, rc.screen_width, rc.screen_height);
	set_background(rc);
	raycast(&rc);
	draw_map(rc);
	image_to_window(rc.mlx, rc.background, 0, 0);
	image_to_window(rc.mlx, rc.screen, 0, 0);
	mlx_loop_hook(rc.mlx, game_loop, &rc);
	mlx_loop(rc.mlx);
	mlx_terminate(rc.mlx);
	free_map(rc, rc.map);
	system("leaks -q cub3D");
	return (EXIT_SUCCESS);
}
