/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 13:31:41 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/16 20:55:11 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "MLX42.h"
#include "info.h"

// int worldMap[24][24]=
// {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

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

static mlx_image_t* image;
static mlx_image_t* rays;

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

t_info	init_info(void)
{
	t_info	info;

	info.screen_width = 800;
	info.screen_height = 600;
	info.map_width = 8;
	info.map_height = 8;
	info.cpx = 0;
	info.cpy = 0.66;
	info.px = 4;
	info.py = 2;
	info.pdx = -1;
	info.pdy = 0;
	info.rdx = 0;
	info.rdy = 0;
	info.mlx = mlx_init(info.screen_width, info.screen_height, "cub3D", true);
	return (info);
}

/* Function that draws a line from 1 point to another using bresenheim algorithm */
void	draw_line(mlx_image_t* image, int x0, int y0, int x1, int y1, uint32_t color)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		mlx_put_pixel(image, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	mlx_draw_rect(mlx_image_t* image, int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color)
{
	for (int32_t i = x; i < x + width; ++i)
	{
		for (int32_t j = y; j < y + height; ++j)
		{
			mlx_put_pixel(image, i, j, color);
		}
	}
}

void	draw(t_info info)
{
	int		side;

	mlx_draw_rect(image, 0, 0, info.screen_width, info.screen_height, BLACK);
	for (int x = 0; x < info.screen_width; x++)
	{
		// Calculate ray direction and initial position
		double cameraX = 2 * x / (double)info.screen_width - 1;
		info.rdx = info.pdx + info.cpx * cameraX;
		info.rdy = info.pdy + info.cpy * cameraX;

		// Map position
		int mapX = (int)info.px;
		int mapY = (int)info.py;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// Delta distance calculation
		double deltaDistX = (info.rdx == 0) ? 1e30 : fabs(1 / info.rdx);
		double deltaDistY = (info.rdy == 0) ? 1e30 : fabs(1 / info.rdy);
		double perpWallDist;

		// Step calculation
		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (info.rdx < 0) {
			stepX = -1;
			sideDistX = (info.px - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - info.px) * deltaDistX;
		}

		if (info.rdy < 0) {
			stepY = -1;
			sideDistY = (info.py - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - info.py) * deltaDistY;
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
			if (worldMap[mapY][mapX] == 1)
			{
				//draw_line(image, info.px * 16, info.py * 16, mapX * 16, mapY * 16, ORANGE);
				break;
			}
		}

		// Calculate distance to the wall
		if (side == 0) {
		perpWallDist = (sideDistX - deltaDistX);
		} else {
		perpWallDist = (sideDistY - deltaDistY);
		}

		// Calculate wall height
		int lineHeight = (int)(info.screen_height / perpWallDist);

		// Calculate draw start and end positions for the wall
		int drawStart = -lineHeight / 2 + info.screen_height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + info.screen_height / 2;
		if (drawEnd >= info.screen_height)
			drawEnd = info.screen_height - 1;

		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		// Draw the wall column
		double wallX; //where exactly the wall was hit
		int color;
		if(side == 0)
		{
			wallX = info.py + perpWallDist * info.rdy;
			color = RED;
		}
		else
		{
			wallX = info.px + perpWallDist * info.rdx;
			color = BLUE;
		}
		wallX -= floor((wallX));
		int	y;

		y = 0;
		while (y < info.screen_height)
		{
			if (y >= drawStart && y < drawEnd)
				mlx_put_pixel(image, x, y, color);
			else if (y < info.screen_height / 2)
				mlx_put_pixel(image, x, y, MAUVE);
			else
				mlx_put_pixel(image, x, y, PANTONE448C);
			y++;
		}
	}
}

/* Draw a minimap that shows the walls and the player position.
Make it so that every tile is 16 by 16 and every tile has a 1 pixel on its edge.

Lastly, draw a direction line from the player.*/
void	draw_map(t_info info)
{
	int		tile_size;
	int		x;
	int		y;

	tile_size = 32;
	x = 0;
	mlx_draw_rect(image, 0, 0, info.map_width * tile_size, info.map_height * tile_size, BLACK);
	while (x < info.map_width)
	{
		y = 0;
		while (y < info.map_height)
		{
			if (worldMap[y][x] == 1)
			{
				mlx_draw_rect(image, x * tile_size + 1, y * tile_size + 1, tile_size - 2, tile_size - 2, WHITE);
			}
			else
			{
				mlx_draw_rect(image, x * tile_size + 1, y * tile_size + 1, tile_size - 2, tile_size - 2, DARKGRAY);
			}
			y++;
		}
		x++;
	}
	mlx_draw_rect(image, info.px * tile_size - 2, info.py * tile_size - 2, 5, 5, PURPLE);
	draw_line(image, info.px * tile_size, info.py * tile_size, info.px * tile_size + info.pdx * (tile_size / 2), info.py * tile_size + info.pdy * (tile_size / 2), RED);

	// int r, mx, my, mp, dof;
	// double rx, ry, ra, xo, yo;
	// ra = fix_ang(atan2(info.pdy, info.pdx) * (180.0 / M_PI) + 30); // Angle of the ray
	// printf("ra: %f\n", ra);
	// r = 0;
	// while (r < 1)
	// {
	// 	// Draw a line from the player until you hit the horizontal part of the wall
	// 	dof = 0; // depth of field
	// 	double aTan = -1 / tan(ra);
	// 	if (ra > M_PI)
	// 	{
	// 		ry = (((int)info.py >> 6) << 6) - 0.0001;
	// 		rx = (info.py - ry) * aTan + info.px;
	// 		yo = -64;
	// 		xo = -yo * aTan;
	// 	}
	// 	if (ra < M_PI)
	// 	{
	// 		ry = (((int)info.py >> 6) << 6) + 64;
	// 		rx = (info.py - ry) * aTan + info.px;
	// 		yo = 64;
	// 		xo = -yo * aTan;
	// 	}
	// 	if (ra == 0 || ra == M_PI)
	// 	{
	// 		rx = info.px;
	// 		ry = info.py;
	// 		dof = 8; // update this to not be hardcoded
	// 	}
	// 	while (dof < 8)
	// 	{
	// 		//printf("rx: %f, ry: %f, dof: %d, mp: %d\n", rx, ry, dof, mp);
	// 		mx = (int)(rx) >> 6;
	// 		my = (int)(ry) >> 6;
	// 		mp = my * info.map_width + mx;
	// 		if (mp > 0 && mp < info.map_width * info.map_height && worldMap[mp] == 1)
	// 		{
	// 			dof = 8;
	// 		}
	// 		else
	// 		{
	// 			rx += xo;
	// 			ry += yo;
	// 			dof += 1;
	// 		}
	// 	}
	// 	//printf("rx: %f, ry: %f, dof: %d, mx: %d, my: %d, mp: %d\n", rx, ry, dof, mx, my, mp);
	// 	draw_line(image, info.px * tile_size, info.py * tile_size, fabs(rx), fabs(ry), RED);
	// 	r++;
	// }

	// // Draw a line from the player until you hit the vertical part of the wall
}

void	ft_hook(void *param)
{
	t_info	*info;
	mlx_t	*mlx;
	double rotationSpeed = 0.05; // Adjust the value as needed
	double movementSpeed = 0.05; // Adjust the value as needed

	info = param;
	mlx = info->mlx;
	double move_x = info->pdx * movementSpeed;
	double move_y = info->pdy * movementSpeed;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		printf("px: %f, py: %f\n", info->px, info->py);
		if (worldMap[(int)info->py][(int)(info->px + move_x)] == 0)
			info->px += move_x;
		if (worldMap[(int)(info->py + move_y)][(int)info->px] == 0)
			info->py += move_y;
		draw(*info);
		draw_map(*info);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		printf("px: %f, py: %f\n", info->px, info->py);
		if (worldMap[(int)info->py][(int)(info->px - move_x)] == 0)
			info->px -= move_x;
		if (worldMap[(int)(info->py - move_y)][(int)info->px] == 0)
			info->py -= move_y;
		draw(*info);
		draw_map(*info);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		double oldDirX = info->pdx;
		info->pdx = info->pdx * cos(rotationSpeed) - info->pdy * sin(rotationSpeed);
		info->pdy = oldDirX * sin(rotationSpeed) + info->pdy * cos(rotationSpeed);
		double oldPlaneX = info->cpx;
		info->cpx = info->cpx * cos(rotationSpeed) - info->cpy * sin(rotationSpeed);
		info->cpy = oldPlaneX * sin(rotationSpeed) + info->cpy * cos(rotationSpeed);
		draw(*info);
		draw_map(*info);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		double oldDirX = info->pdx;
		info->pdx = info->pdx * cos(-rotationSpeed) - info->pdy * sin(-rotationSpeed);
		info->pdy = oldDirX * sin(-rotationSpeed) + info->pdy * cos(-rotationSpeed);
		double oldPlaneX = info->cpx;
		info->cpx = info->cpx * cos(-rotationSpeed) - info->cpy * sin(-rotationSpeed);
		info->cpy = oldPlaneX * sin(-rotationSpeed) + info->cpy * cos(-rotationSpeed);
		draw(*info);
		draw_map(*info);
	}
}

// -----------------------------------------------------------------------------

int	main(int argc, char *argv[])
{
	t_info	info;

	info = init_info();
	if (!info.mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(info.mlx, info.screen_width, info.screen_height)))
	{
		mlx_close_window(info.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	draw(info);
	draw_map(info);
	if (mlx_image_to_window(info.mlx, image, 0, 0) == -1)
	{
		mlx_close_window(info.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(info.mlx, ft_hook, &info);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);
	return (EXIT_SUCCESS);
}
