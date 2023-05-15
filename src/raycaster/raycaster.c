/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 13:31:41 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/15 18:23:06 by fholwerd      ########   odam.nl         */
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

	info.screen_width = 1600;
	info.screen_height = 900;
	info.map_width = 8;
	info.map_height = 8;
	info.cam_plane_x = 0;
	info.cam_plane_y = 0.66;
	info.pos_x = 4;
	info.pos_y = 2;
	info.dir_x = -1;
	info.dir_y = 0;
	info.ray_dir_x = 0;
	info.ray_dir_y = 0;
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

void	draw(t_info info)
{
	int		side;

	for (int x = 0; x < info.screen_width; x++)
	{
		// Calculate ray direction and initial position
		double cameraX = 2 * x / (double)info.screen_width - 1;
		info.ray_dir_x = info.dir_x + info.cam_plane_x * cameraX;
		info.ray_dir_y = info.dir_y + info.cam_plane_y * cameraX;

		// Map position
		int mapX = (int)info.pos_x;
		int mapY = (int)info.pos_y;

		// Delta distance calculation
		double deltaDistX = fabs(1 / info.ray_dir_x);
		double deltaDistY = fabs(1 / info.ray_dir_y);

		// Step calculation
		int stepX, stepY;
		int sideDistX, sideDistY;

		if (info.ray_dir_x < 0) {
			stepX = -1;
			sideDistX = (info.pos_x - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - info.pos_x) * deltaDistX;
		}

		if (info.ray_dir_y < 0) {
			stepY = -1;
			sideDistY = (info.pos_y - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - info.pos_y) * deltaDistY;
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
				//draw_line(image, info.pos_x * 16, info.pos_y * 16, mapX * 16, mapY * 16, ORANGE);
				break;
			}
		}

		// Calculate distance to the wall
		double perpWallDist;
		if (side == 0) {
		perpWallDist = (mapX - info.pos_x + (1 - stepX) / 2) / info.ray_dir_x;
		} else {
		perpWallDist = (mapY - info.pos_y + (1 - stepY) / 2) / info.ray_dir_y;
		}

		// Calculate wall height
		int lineHeight = (int)(info.screen_height / perpWallDist);

		// Calculate draw start and end positions for the wall
		int drawStart = -lineHeight / 2 + info.screen_height / 2;
		if (drawStart < 0) {
		drawStart = 0;
		}
		int drawEnd = lineHeight / 2 + info.screen_height / 2;
		if (drawEnd >= info.screen_height) {
		drawEnd = info.screen_height - 1;
		}

		// Draw the wall column
		for (int y = 0; y < info.screen_height; y++)
		{
			if (y >= drawStart && y <= drawEnd)
			{
				if (side == 0)
				{
					if (info.ray_dir_x > 0)
						mlx_put_pixel(image, info.screen_width - x, y, RED);
					else
						mlx_put_pixel(image, info.screen_width - x, y, YELLOW);
				}
				else
				{
					if (info.ray_dir_y > 0)
						mlx_put_pixel(image, info.screen_width - x, y, GREEN);
					else
						mlx_put_pixel(image, info.screen_width - x, y, BLUE);
				}
			}
			else
			{
				if (y < info.screen_height / 2)
					mlx_put_pixel(image, info.screen_width - x, y, SKYBLUE);
				else
					mlx_put_pixel(image, info.screen_width - x, y, DARKGRAY);
			}
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

/* Draw a minimap that shows the walls and the player position.
Make it so that every tile is 16 by 16 and every tile has a 1 pixel on its edge.

Lastly, draw a direction line from the player.*/
void	draw_map(t_info info)
{
	int		tile_size;
	int		x;
	int		y;

	tile_size = 64;
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
	mlx_draw_rect(image, info.pos_x * tile_size - 2, info.pos_y * tile_size - 2, 5, 5, PURPLE);
	draw_line(image, info.pos_x * tile_size, info.pos_y * tile_size, info.pos_x * tile_size + info.dir_x * (tile_size / 2), info.pos_y * tile_size + info.dir_y * (tile_size / 2), RED);

	// int r, mx, my, mp, dof;
	// double rx, ry, ra, xo, yo;
	// ra = fix_ang(atan2(info.dir_y, info.dir_x) * (180.0 / M_PI) + 30); // Angle of the ray
	// printf("ra: %f\n", ra);
	// r = 0;
	// while (r < 1)
	// {
	// 	// Draw a line from the player until you hit the horizontal part of the wall
	// 	dof = 0; // depth of field
	// 	double aTan = -1 / tan(ra);
	// 	if (ra > M_PI)
	// 	{
	// 		ry = (((int)info.pos_y >> 6) << 6) - 0.0001;
	// 		rx = (info.pos_y - ry) * aTan + info.pos_x;
	// 		yo = -64;
	// 		xo = -yo * aTan;
	// 	}
	// 	if (ra < M_PI)
	// 	{
	// 		ry = (((int)info.pos_y >> 6) << 6) + 64;
	// 		rx = (info.pos_y - ry) * aTan + info.pos_x;
	// 		yo = 64;
	// 		xo = -yo * aTan;
	// 	}
	// 	if (ra == 0 || ra == M_PI)
	// 	{
	// 		rx = info.pos_x;
	// 		ry = info.pos_y;
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
	// 	draw_line(image, info.pos_x * tile_size, info.pos_y * tile_size, fabs(rx), fabs(ry), RED);
	// 	r++;
	// }

	// // Draw a line from the player until you hit the vertical part of the wall
}
void	ft_hook(void *param)
{
	t_info	*info;
	mlx_t	*mlx;
	double rotationSpeed = 0.1; // Adjust the value as needed
	double movementSpeed = 0.1; // Adjust the value as needed

	info = param;
	mlx = info->mlx;
	double move_x = info->dir_x * movementSpeed;
	double move_y = info->dir_y * movementSpeed;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		printf("pos_x: %f, pos_y: %f\n", info->pos_x, info->pos_y);
		if (worldMap[(int)info->pos_y][(int)(info->pos_x + move_x)] == 0)
			info->pos_x += move_x;
		if (worldMap[(int)(info->pos_y + move_y)][(int)info->pos_x] == 0)
			info->pos_y += move_y;
		draw(*info);
		draw_map(*info);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		printf("pos_x: %f, pos_y: %f\n", info->pos_x, info->pos_y);
		if (worldMap[(int)info->pos_y][(int)(info->pos_x - move_x)] == 0)
			info->pos_x -= move_x;
		if (worldMap[(int)(info->pos_y - move_y)][(int)info->pos_x] == 0)
			info->pos_y -= move_y;
		draw(*info);
		draw_map(*info);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		double oldDirX = info->dir_x;
		info->dir_x = info->dir_x * cos(-rotationSpeed) - info->dir_y * sin(-rotationSpeed);
		info->dir_y = oldDirX * sin(-rotationSpeed) + info->dir_y * cos(-rotationSpeed);
		double oldPlaneX = info->cam_plane_x;
		info->cam_plane_x = info->cam_plane_x * cos(-rotationSpeed) - info->cam_plane_y * sin(-rotationSpeed);
		info->cam_plane_y = oldPlaneX * sin(-rotationSpeed) + info->cam_plane_y * cos(-rotationSpeed);
		draw(*info);
		draw_map(*info);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		double oldDirX = info->dir_x;
		info->dir_x = info->dir_x * cos(rotationSpeed) - info->dir_y * sin(rotationSpeed);
		info->dir_y = oldDirX * sin(rotationSpeed) + info->dir_y * cos(rotationSpeed);
		double oldPlaneX = info->cam_plane_x;
		info->cam_plane_x = info->cam_plane_x * cos(rotationSpeed) - info->cam_plane_y * sin(rotationSpeed);
		info->cam_plane_y = oldPlaneX * sin(rotationSpeed) + info->cam_plane_y * cos(rotationSpeed);
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

// int32_t main(int32_t argc, const char* argv[])
// {
// 	mlx_t* mlx;

// 	(void)argc;
// 	(void)argv;
// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}

// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
