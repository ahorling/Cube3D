/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 13:31:41 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 16:41:52 by fholwerd      ########   odam.nl         */
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
#include "info.h"
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

static mlx_image_t *rays;
static mlx_texture_t *texture[4];

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
	rc.mspeed = 0.05;
	rc.rspeed = 0.05;
	rc.pitch = 0;
	rc.mlx = mlx_init(rc.screen_width, rc.screen_height, "cub3D", true);
	if (!rc.mlx)
		stop("Failed to initialize mlx");
	return (rc);
}

void	set_background(t_raycaster rc)
{
	/* for rc.background set the floor color to rc.floor_color and the ceiling color to rc.ceiling_color */
	draw_rect(rc.background, rect(0, 0, rc.screen_width, rc.screen_height / 2 + rc.pitch), rc.ceiling_color);
	draw_rect(rc.background, rect(0, rc.screen_height / 2 + rc.pitch, rc.screen_width, rc.screen_height / 2 - rc.pitch), rc.floor_color);
}

// Length of ray from current position to next x or y-side
// Delta distance calculation
static void delta_distance_calculation(t_raycaster *rc)
{
	if (rc->rdx == 0)
		rc->d_dist_x = 1e30;
	else
		rc->d_dist_x = fabs(1 / rc->rdx);
	if (rc->rdy == 0)
		rc->d_dist_y = 1e30;
	else
		rc->d_dist_y = fabs(1 / rc->rdy);
}

static void step_calculation(t_raycaster *rc)
{
	if (rc->rdx < 0) {
		rc->step_x = -1;
		rc->s_dist_x = (rc->px - rc->map_x) * rc->d_dist_x;
	} else {
		rc->step_x = 1;
		rc->s_dist_x = (rc->map_x + 1.0 - rc->px) * rc->d_dist_x;
	}

	if (rc->rdy < 0) {
		rc->step_y = -1;
		rc->s_dist_y = (rc->py - rc->map_y) * rc->d_dist_y;
	} else {
		rc->step_y = 1;
		rc->s_dist_y = (rc->map_y + 1.0 - rc->py) * rc->d_dist_y;
	}
}

void	cast_single_ray(t_raycaster *rc)
{
	// Calculate ray direction and initial position
	rc->cx = 2 * rc->x / (double)rc->screen_width - 1;
	rc->rdx = rc->pdx + rc->cpx * rc->cx;
	rc->rdy = rc->pdy + rc->cpy * rc->cx;

	// Map position
	rc->map_x = (int)rc->px;
	rc->map_y = (int)rc->py;

	//length of ray from current position to next x or y-side

	// Delta distance calculation
	delta_distance_calculation(rc);

	// Step calculation
	step_calculation(rc);

	// Perform DDA
	while (1)
	{
		// Jump to the next map square
		if (rc->s_dist_x < rc->s_dist_y) {
			rc->s_dist_x += rc->d_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0; // Side is set to 0 for vertical wall hit
		} else {
			rc->s_dist_y += rc->d_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1; // Side is set to 1 for horizontal wall hit
		}

		// Check if the ray has hit a wall
		if (rc->map[rc->map_y][rc->map_x] == 1)
			break;
	}
	draw_line(rays, pt(rc->px * rc->tile_size, rc->py * rc->tile_size), pt(rc->map_x * rc->tile_size, rc->map_y * rc->tile_size), ORANGE);
	//draw_line(rays, rc->px * rc->tile_size, rc->py * rc->tile_size, rc->map_x * rc->tile_size, rc->map_y * rc->tile_size, ORANGE);

	// Calculate distance to the wall
	if (rc->side == 0) {
	rc->pwd = (rc->s_dist_x - rc->d_dist_x);
	} else {
	rc->pwd = (rc->s_dist_y - rc->d_dist_y);
	}

	// Calculate wall height
	rc->line_height = (int)(rc->screen_height / rc->pwd);

	// Calculate draw start and end positions for the wall
	rc->draw_start = -rc->line_height / 2 + rc->screen_height / 2 + rc->pitch;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + rc->screen_height / 2 + rc->pitch;
	if (rc->draw_end >= rc->screen_height)
		rc->draw_end = rc->screen_height - 1;

	rc->tex_num = rc->map[rc->map_x][rc->map_y] - 1; //1 subtracted from it so that texture 0 can be used!

	// Draw the wall column
	if(rc->side == 0)
		rc->wall_x = rc->py + rc->pwd * rc->rdy;
	else
		rc->wall_x = rc->px + rc->pwd * rc->rdx;
	rc->wall_x -= floor((rc->wall_x));

	//x coordinate on the texture
	if (rc->side == 0 && rc->rdx > 0)
		rc->tex_num = 0;
	if (rc->side == 0 && rc->rdx < 0)
		rc->tex_num = 1;
	if (rc->side == 1 && rc->rdy > 0)
		rc->tex_num = 2;
	if (rc->side == 1 && rc->rdy < 0)
		rc->tex_num = 3;
	rc->tex = texture[rc->tex_num];
	rc->tex_width = rc->tex->width;
	rc->tex_height = rc->tex->height;
	rc->tex_x = (int)(rc->wall_x * (double)(rc->tex_width));
	if(rc->side == 0 && rc->rdx > 0)
		rc->tex_x = rc->tex_width - rc->tex_x - 1;
	if(rc->side == 1 && rc->rdy < 0)
		rc->tex_x = rc->tex_width - rc->tex_x - 1;

	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	rc->tex_step = (double)rc->tex_height / (double)rc->line_height;
	// Starting texture coordinate
	rc->tex_pos = (rc->draw_start - rc->pitch - rc->screen_height / 2 + rc->line_height / 2) * rc->tex_step;

	rc->y = 0;
	while (rc->y < rc->screen_height)
	{
		if (rc->y >= rc->draw_start && rc->y < rc->draw_end)
		{
			// Cast the texture coordinate to integer, and mask with (rc->tex_height - 1) in case of overflow
			int texY = (int)rc->tex_pos;
			rc->tex_pos += rc->tex_step;
			rc->color = correct_color(&rc->tex->pixels[(rc->tex_height * texY + (rc->tex->width - rc->tex_x - 1)) * 4]);
			// rc->color = correct_color(&rc->tex->pixels[(rc->tex_height * texY + (rc->tex_x)) * 4]);
			put_pixel(rc->screen, rc->x, rc->y, rc->color);
		}
		else
			put_pixel(rc->screen, rc->x, rc->y, TRANSPARENT);
		rc->y++;
	}
}

void	raycast(t_raycaster *rc)
{
	draw_rect(rays, rect(0, 0, rc->map_width * rc->tile_size, rc->map_height * rc->tile_size), TRANSPARENT);
	rc->x = 0;
	while (rc->x < rc->screen_width)
	{
		cast_single_ray(rc);
		rc->x++;
	}
}

void	game_loop(void *param)
{
	t_raycaster	*rc;

	rc = param;
	movement(rc);
	raycast(rc);
	draw_map(*rc);
}

// -----------------------------------------------------------------------------

mlx_image_t	*init_image(mlx_t *mlx, int width, int height)
{
	mlx_image_t	*image;

	image = mlx_new_image(mlx, width, height);
	if (!image)
		stop("Failed to initialize image");
	return (image);
}

void	image_to_window(mlx_t *mlx, mlx_image_t *image, int x, int y)
{
	if (mlx_image_to_window(mlx, image, x, y) == -1)
		stop("Failed to put image to window");
}

int	main(int argc, char *argv[])
{
	t_raycaster	rc;

	rc = init_raycaster();
	if (!rc.mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	texture[0] = mlx_load_png("mario2.png");
	texture[1] = mlx_load_png("stone.png");
	texture[2] = mlx_load_png("single_pixel.png");
	texture[3] = mlx_load_png("wt_logo.png");
	rc.background = init_image(rc.mlx, rc.screen_width, rc.screen_height);
	rc.screen = init_image(rc.mlx, rc.screen_width, rc.screen_height);
	rays = init_image(rc.mlx, rc.map_width * rc.tile_size, rc.map_height * rc.tile_size);
	set_background(rc);
	raycast(&rc);
	draw_map(rc);
	image_to_window(rc.mlx, rc.background, 0, 0);
	image_to_window(rc.mlx, rc.screen, 0, 0);
	image_to_window(rc.mlx, rays, 0, 0);
	mlx_loop_hook(rc.mlx, game_loop, &rc);
	mlx_loop(rc.mlx);
	mlx_terminate(rc.mlx);
	free_map(rc, rc.map);
	return (EXIT_SUCCESS);
}
