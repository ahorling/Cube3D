/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 13:31:41 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 16:16:14 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "draw_line.h"
#include "draw_rectangle.h"
#include "info.h"
#include "minimap.h"
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

double deg_to_rad(int a)
{
	return (a * M_PI / 180.0);
}
int fix_ang(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

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
			printf("map: %d, worldMap: %d\n", map[i][j], worldMap[i][j]);
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
	rc.mlx = mlx_init(rc.screen_width, rc.screen_height, "cub3D", true);
	return (rc);
}

/* Function that draws a line from 1 point to another using bresenheim algorithm */
// void	draw_line(mlx_image_t* image, int x0, int y0, int x1, int y1, uint32_t color)
// {
// 	int		dx;
// 	int		dy;
// 	int		sx;
// 	int		sy;
// 	int		err;
// 	int		e2;

// 	dx = abs(x1 - x0);
// 	dy = abs(y1 - y0);
// 	sx = x0 < x1 ? 1 : -1;
// 	sy = y0 < y1 ? 1 : -1;
// 	err = (dx > dy ? dx : -dy) / 2;
// 	while (1)
// 	{
// 		mlx_put_pixel(image, x0, y0, color);
// 		if (x0 == x1 && y0 == y1)
// 			break ;
// 		e2 = err;
// 		if (e2 > -dx)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 < dy)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

void	clear_screen(t_raycaster rc)
{
	draw_rect(rc.screen, rect(0, 0, rc.screen_width, rc.screen_height), BLACK);
	draw_rect(rays, rect(0, 0, rc.map_width * rc.tile_size, rc.map_height * rc.tile_size), TRANSPARENT);
}

int	correct_color(u_int8_t *pixel)
{
	int	rgba;

	rgba = 0;
	rgba += pixel[0] << 24;
	rgba += pixel[1] << 16;
	rgba += pixel[2] << 8;
	rgba += pixel[3];
	return (rgba);
}

void	draw(t_raycaster rc)
{
	int	side;

	//clear_screen(rc);
	//draw_rect(rc.screen, rect(0, 1, rc.screen_width, rc.screen_height / 2), rc.ceiling_color);
	//draw_rect(rc.screen, rect(0, rc.screen_height / 2, rc.screen_width, rc.screen_height / 2), rc.floor_color);
	for (int x = 0; x < rc.screen_width; x++)
	{
		// Calculate ray direction and initial position
		double cameraX = 2 * x / (double)rc.screen_width - 1;
		rc.rdx = rc.pdx + rc.cpx * cameraX;
		rc.rdy = rc.pdy + rc.cpy * cameraX;

		// Map position
		int mapX = (int)rc.px;
		int mapY = (int)rc.py;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// Delta distance calculation
		double deltaDistX = (rc.rdx == 0) ? 1e30 : fabs(1 / rc.rdx);
		double deltaDistY = (rc.rdy == 0) ? 1e30 : fabs(1 / rc.rdy);
		double perpWallDist;

		// Step calculation
		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rc.rdx < 0) {
			stepX = -1;
			sideDistX = (rc.px - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - rc.px) * deltaDistX;
		}

		if (rc.rdy < 0) {
			stepY = -1;
			sideDistY = (rc.py - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - rc.py) * deltaDistY;
		}

		// Perform DDA
		while (1)
		{
			// Jump to the next map square
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0; // Side is set to 0 for vertical wall hit
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1; // Side is set to 1 for horizontal wall hit
			}

			// Check if the ray has hit a wall
			if (rc.map[mapY][mapX] == 1)
				break;
		}
		// draw_line(rays, rc.px * rc.tile_size, rc.py * rc.tile_size, mapX * rc.tile_size, mapY * rc.tile_size, ORANGE);

		// Calculate distance to the wall
		if (side == 0) {
		perpWallDist = (sideDistX - deltaDistX);
		} else {
		perpWallDist = (sideDistY - deltaDistY);
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

		int texNum = rc.map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

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

void	draw_player(t_raycaster rc)
{
	draw_rect(rc.screen, rect(rc.px * rc.tile_size - 2, rc.py * rc.tile_size - 2, 5, 5), PURPLE);
	draw_line(rc.screen, pt(rc.px * rc.tile_size, rc.py * rc.tile_size), pt(rc.px * rc.tile_size + rc.pdx * (rc.tile_size / 2), rc.py * rc.tile_size + rc.pdy * (rc.tile_size / 2)), RED);
}

void	ft_hook(void *param)
{
	t_raycaster	*rc;
	mlx_t	*mlx;
	double rotationSpeed = 0.05; // Adjust the value as needed
	double movementSpeed = 0.05; // Adjust the value as needed

	rc = param;
	mlx = rc->mlx;
	double move_x = rc->pdx * movementSpeed;
	double move_y = rc->pdy * movementSpeed;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		printf("px: %f, py: %f\n", rc->px, rc->py);
		if (rc->map[(int)rc->py][(int)(rc->px + move_x)] == 0)
			rc->px += move_x;
		if (rc->map[(int)(rc->py + move_y)][(int)rc->px] == 0)
			rc->py += move_y;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		printf("px: %f, py: %f\n", rc->px, rc->py);
		if (rc->map[(int)rc->py][(int)(rc->px - move_x)] == 0)
			rc->px -= move_x;
		if (rc->map[(int)(rc->py - move_y)][(int)rc->px] == 0)
			rc->py -= move_y;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		double oldDirX = rc->pdx;
		rc->pdx = rc->pdx * cos(-rotationSpeed) - rc->pdy * sin(-rotationSpeed);
		rc->pdy = oldDirX * sin(-rotationSpeed) + rc->pdy * cos(-rotationSpeed);
		double oldPlaneX = rc->cpx;
		rc->cpx = rc->cpx * cos(-rotationSpeed) - rc->cpy * sin(-rotationSpeed);
		rc->cpy = oldPlaneX * sin(-rotationSpeed) + rc->cpy * cos(-rotationSpeed);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D) || mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = rc->pdx;
		rc->pdx = rc->pdx * cos(rotationSpeed) - rc->pdy * sin(rotationSpeed);
		rc->pdy = oldDirX * sin(rotationSpeed) + rc->pdy * cos(rotationSpeed);
		double oldPlaneX = rc->cpx;
		rc->cpx = rc->cpx * cos(rotationSpeed) - rc->cpy * sin(rotationSpeed);
		rc->cpy = oldPlaneX * sin(rotationSpeed) + rc->cpy * cos(rotationSpeed);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Q))
	{
		printf("px: %f, py: %f\n", rc->px, rc->py);
		if (rc->map[(int)(rc->py - move_x)][(int)rc->px] == 0)
			rc->py -= move_x;
		if (rc->map[(int)rc->py][(int)(rc->px + move_y)] == 0)
			rc->px += move_y;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_E))
	{
		printf("px: %f, py: %f\n", rc->px, rc->py);
		if (rc->map[(int)(rc->py + move_x)][(int)rc->px] == 0)
			rc->py += move_x;
		if (rc->map[(int)rc->py][(int)(rc->px - move_y)] == 0)
			rc->px -= move_y;
	}
	draw(*rc);
	draw_map(*rc);
	draw_player(*rc);
	printf("delta_time: %f\n", mlx->delta_time);
}

// -----------------------------------------------------------------------------

// int	main(int argc, char *argv[])
// {
// 	t_raycaster	rc;

// 	rc = init_raycaster();
// 	if (!rc.mlx)
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return (EXIT_FAILURE);
// 	}
// 	texture[0] = mlx_load_png("mario2.png");
// 	texture[1] = mlx_load_png("stone.png");
// 	texture[2] = mlx_load_png("archer.png");
// 	texture[3] = mlx_load_png("wt_logo.png");
// 	if (!(rc.screen = mlx_new_image(rc.mlx, rc.screen_width, rc.screen_height)) || !(rays = mlx_new_image(rc.mlx, rc.map_width * rc.tile_size, rc.map_height * rc.tile_size)))
// 	{
// 		mlx_close_window(rc.mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	draw(rc);
// 	draw_map(rc);
// 	draw_player(rc);
// 	if (mlx_image_to_window(rc.mlx, rc.screen, 0, 0) == -1 || mlx_image_to_window(rc.mlx, rays, 0, 0) == -1)
// 	{
// 		mlx_close_window(rc.mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	mlx_loop_hook(rc.mlx, ft_hook, &rc);
// 	mlx_loop(rc.mlx);
// 	mlx_terminate(rc.mlx);
// 	free_map(rc, rc.map);
// 	return (EXIT_SUCCESS);
// }
