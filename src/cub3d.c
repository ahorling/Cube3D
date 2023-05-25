/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 20:11:43 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/25 20:11:56 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "image_to_window.h"
#include "info.h"
#include "init_image.h"
#include "init_raycaster.h"
#include "minimap.h"
#include "MLX42.h"
#include "movement.h"
#include "raycaster.h"
#include "set_background.h"

/* This function will be called every frame. It will handle the movement
of the player and it will raycast and draw the map. */
void	game_loop(void *param)
{
	t_raycaster	*rc;

	rc = param;
	movement(rc);
	raycast(rc);
	draw_map(*rc);
}

/* Takes the info from info and converts it into usable info for the
raycaster scene. It will initialize a couple of images, sets the background
and then it will start raycasting and it will draw the map afterwards.
It also starts the gameloop. */
void	cub3d(t_info *info)
{
	t_raycaster	rc;

	rc = init_raycaster(info);
	rc.background = init_image(rc.mlx, rc.screen_width, rc.screen_height);
	rc.screen = init_image(rc.mlx, rc.screen_width, rc.screen_height);
	if (rc.tile_size > 0)
		rc.minimap = init_image(rc.mlx,
				rc.map_width * rc.tile_size, rc.map_height * rc.tile_size);
	set_background(rc);
	raycast(&rc);
	draw_map(rc);
	image_to_window(rc.mlx, rc.background, 0, 0);
	image_to_window(rc.mlx, rc.screen, 0, 0);
	if (rc.tile_size > 0)
		image_to_window(rc.mlx, rc.minimap, 0, 0);
	mlx_loop_hook(rc.mlx, game_loop, &rc);
	mlx_loop(rc.mlx);
	mlx_terminate(rc.mlx);
	mlx_delete_texture(rc.textures[0]);
	mlx_delete_texture(rc.textures[1]);
	mlx_delete_texture(rc.textures[2]);
	mlx_delete_texture(rc.textures[3]);
}
