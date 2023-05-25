/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_raycaster.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 20:05:12 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/25 20:13:11 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "deg_to_rad.h"
#include "info.h"
#include "load_texture.h"
#include "movement.h"
#include "raycaster.h"
#include "stop.h"

static void	init_player_position(t_raycaster *rc, t_info *info)
{
	rc->px = (double)info->player_x + 0.5;
	rc->py = (double)info->player_y + 0.5;
	rc->pdx = 1;
	rc->pdy = 0;
	if (info->player_direction == 'N')
		rotate_player(rc, deg_to_rad(-90));
	else if (info->player_direction == 'E')
		rotate_player(rc, deg_to_rad(0));
	else if (info->player_direction == 'S')
		rotate_player(rc, deg_to_rad(90));
	else if (info->player_direction == 'W')
		rotate_player(rc, deg_to_rad(180));
}

static void	set_tile_size(t_raycaster *rc)
{
	int	tile_size_x;
	int	tile_size_y;

	tile_size_x = (rc->screen_width / 4) / rc->map_width;
	tile_size_y = (rc->screen_height / 4) / rc->map_height;
	if (tile_size_x < tile_size_y)
		rc->tile_size = tile_size_x;
	else
		rc->tile_size = tile_size_y;
	if (rc->tile_size < 3)
		rc->tile_size = -1;
}

static void	load_textures(t_raycaster *rc, t_info *info)
{
	rc->textures[0] = load_texture(info->east_texture);
	rc->textures[1] = load_texture(info->west_texture);
	rc->textures[2] = load_texture(info->south_texture);
	rc->textures[3] = load_texture(info->north_texture);
	if (!rc->textures[0] || !rc->textures[1] || !rc->textures[2]
		|| !rc->textures[3])
		stop("Failed to load textures");
}

t_raycaster	init_raycaster(t_info *info)
{
	t_raycaster	rc;

	rc.floor_color = info->floor_color;
	rc.ceiling_color = info->ceiling_color;
	rc.screen_width = 1600;
	rc.screen_height = 900;
	rc.map_width = info->map_width;
	rc.map_height = info->map_height;
	rc.map = info->map;
	set_tile_size(&rc);
	rc.cpx = 0;
	rc.cpy = 0.66;
	init_player_position(&rc, info);
	rc.rdx = 0;
	rc.rdy = 0;
	rc.mspeed = 0.04999;
	rc.rspeed = 0.05;
	rc.pitch = 0;
	load_textures(&rc, info);
	rc.mlx = mlx_init(rc.screen_width, rc.screen_height, "cub3D", true);
	if (!rc.mlx)
		stop("Failed to initialize mlx");
	return (rc);
}
