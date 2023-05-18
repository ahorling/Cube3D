/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 13:31:41 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/18 20:06:18 by fholwerd      ########   odam.nl         */
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
#include "raycaster.h"
#include "rectangle.h"

int worldMap[8][8]=
{
	{1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1}
};

static mlx_image_t *rays;
static mlx_texture_t *texture[4];

int	**convert_worldmap(void)
{
	int	**map;
	int	i;
	int	j;

	map = malloc(sizeof(int *) * 8);
	if (!map)
		return (NULL);
	i = 0;
	while (i < 8)
	{
		map[i] = malloc(sizeof(int) * 8);
		if (!map[i])
			return (NULL);
		j = 0;
		while (j < 8)
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

t_raycaster	init_raycaster(void)
{
	t_raycaster	rc;

	rc.floor_color = DARKGRAY;
	rc.ceiling_color = SKYBLUE;
	rc.screen_width = 1280;
	rc.screen_height = 800;
	rc.map_width = 8;
	rc.map_height = 8;
	rc.map = convert_worldmap();
	rc.tile_size = 32;
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
	rc.mlx = mlx_init(rc.screen_width, rc.screen_height, "cub3D", true);
	if (!rc.mlx)
	{
		printf("Error\nFailed to initialize mlx\n");
		exit(EXIT_FAILURE);
	}
	return (rc);
}

void	clear_screen(t_raycaster rc)
{
	draw_rect(rc.screen, rect(0, 0, rc.screen_width, rc.screen_height), BLACK);
	draw_rect(rays, rect(0, 0, rc.map_width * rc.tile_size, rc.map_height * rc.tile_size), TRANSPARENT);
}

void	raycast(t_raycaster rc)
{
	int	side;

	//clear_screen(rc);
	//draw_rect(rc.screen, rect(0, 1, rc.screen_width, rc.screen_height / 2), rc.ceiling_color);
	//draw_rect(rc.screen, rect(0, rc.screen_height / 2, rc.screen_width, rc.screen_height / 2), rc.floor_color);
	for (int x = 0; x < rc.screen_width; x++)
	{
		// Calculate ray direction and initial position
		rc.cx = 2 * x / (double)rc.screen_width - 1;
		rc.rdx = rc.pdx + rc.cpx * rc.cx;
		rc.rdy = rc.pdy + rc.cpy * rc.cx;

		// Map position
		rc.map_x = (int)rc.px;
		rc.map_y = (int)rc.py;

		//length of ray from current position to next x or y-side

		// Delta distance calculation
		rc.d_dist_x = (rc.rdx == 0) ? 1e30 : fabs(1 / rc.rdx);
		rc.d_dist_y = (rc.rdy == 0) ? 1e30 : fabs(1 / rc.rdy);
		double perpWallDist;

		// Step calculation
		int hit = 0;
		int side;

		if (rc.rdx < 0) {
			rc.step_x = -1;
			rc.s_dist_x = (rc.px - rc.map_x) * rc.d_dist_x;
		} else {
			rc.step_x = 1;
			rc.s_dist_x = (rc.map_x + 1.0 - rc.px) * rc.d_dist_x;
		}

		if (rc.rdy < 0) {
			rc.step_y = -1;
			rc.s_dist_y = (rc.py - rc.map_y) * rc.d_dist_y;
		} else {
			rc.step_y = 1;
			rc.s_dist_y = (rc.map_y + 1.0 - rc.py) * rc.d_dist_y;
		}

		// Perform DDA
		while (1)
		{
			// Jump to the next map square
			if (rc.s_dist_x < rc.s_dist_y) {
				rc.s_dist_x += rc.d_dist_x;
				rc.map_x += rc.step_x;
				side = 0; // Side is set to 0 for vertical wall hit
			} else {
				rc.s_dist_y += rc.d_dist_y;
				rc.map_y += rc.step_y;
				side = 1; // Side is set to 1 for horizontal wall hit
			}

			// Check if the ray has hit a wall
			if (rc.map[rc.map_y][rc.map_x] == 1)
				break;
		}
		// draw_line(rays, rc.px * rc.tile_size, rc.py * rc.tile_size, rc.map_x * rc.tile_size, rc.map_y * rc.tile_size, ORANGE);

		// Calculate distance to the wall
		if (side == 0) {
		perpWallDist = (rc.s_dist_x - rc.d_dist_x);
		} else {
		perpWallDist = (rc.s_dist_y - rc.d_dist_y);
		}

		// Calculate wall height
		int lineHeight = (int)(rc.screen_height / perpWallDist);

		int pitch = 0;

		// Calculate draw start and end positions for the wall
		int drawStart = -lineHeight / 2 + rc.screen_height / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + rc.screen_height / 2 + pitch;
		if (drawEnd >= rc.screen_height)
			drawEnd = rc.screen_height - 1;

		int texNum = rc.map[rc.map_x][rc.map_y] - 1; //1 subtracted from it so that texture 0 can be used!

		// Draw the wall column
		double wallX; //where exactly the wall was hit
		int color;
		if(side == 0)
		{
			wallX = rc.py + perpWallDist * rc.rdy;
			color = RED;
		}
		else
		{
			wallX = rc.px + perpWallDist * rc.rdx;
			color = BLUE;
		}
		wallX -= floor((wallX));
		//x coordinate on the texture
		if (side == 0 && rc.rdx > 0)
			texNum = 0;
		if (side == 0 && rc.rdx < 0)
			texNum = 1;
		if (side == 1 && rc.rdy > 0)
			texNum = 2;
		if (side == 1 && rc.rdy < 0)
			texNum = 3;
		mlx_texture_t *tex = texture[texNum];
		int texWidth = tex->width;
		int texHeight = tex->height;
		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rc.rdx > 0)
			texX = texWidth - texX - 1;
		if(side == 1 && rc.rdy < 0)
			texX = texWidth - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = (double)texHeight / (double)lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - pitch - rc.screen_height / 2 + lineHeight / 2) * step;
		// for(int y = drawStart; y < drawEnd; y++)
		// {
		// 	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		// 	int texY = (int)texPos & (texHeight - 1);
		// 	texPos += step;
		// 	color = texture->pixels[texHeight * texY + texX];
		// 	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// 	if(side == 1) color = (color >> 1) & 8355711;
		// 	mlx_put_pixel(rc.screen, x, y, color);
		// }

		int y = 0;
		while (y < rc.screen_height)
		{
			if (y >= drawStart && y <= drawEnd)
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				color = correct_color(&tex->pixels[(texHeight * texY + (tex->width - texX - 1)) * 4]);
				mlx_put_pixel(rc.screen, x, y, color);
			}
			else if (y < drawStart)
				mlx_put_pixel(rc.screen, x, y, SKYBLUE);
			else
				mlx_put_pixel(rc.screen, x, y, DARKBROWN);
			y++;
		}
	}
}

void	game_loop(void *param)
{
	t_raycaster	*rc;

	rc = param;
	movement(rc);
	raycast(*rc);
	draw_map(*rc);
}

// -----------------------------------------------------------------------------

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
	texture[2] = mlx_load_png("stone_bricks.png");
	texture[3] = mlx_load_png("wt_logo.png");
	if (!(rc.screen = mlx_new_image(rc.mlx, rc.screen_width, rc.screen_height)) || !(rays = mlx_new_image(rc.mlx, rc.map_width * rc.tile_size, rc.map_height * rc.tile_size)))
	{
		mlx_close_window(rc.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	raycast(rc);
	draw_map(rc);
	if (mlx_image_to_window(rc.mlx, rc.screen, 0, 0) == -1 || mlx_image_to_window(rc.mlx, rays, 0, 0) == -1)
	{
		mlx_close_window(rc.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(rc.mlx, game_loop, &rc);
	mlx_loop(rc.mlx);
	mlx_terminate(rc.mlx);
	free_map(rc, rc.map);
	return (EXIT_SUCCESS);
}
