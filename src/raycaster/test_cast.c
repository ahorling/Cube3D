/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cast.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 13:31:41 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/15 21:30:10 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "MLX42.h"
#include "info.h"

int worldMap[]=
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1
};

static mlx_image_t* image;

// Converts degrees to radians
double deg_to_rad(int a)
{
	return (a * M_PI / 180.0);
}
// Normalize angle to be between 0 and 359
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

	info.screen_width = 2048;
	info.screen_height = 1020;
	info.map_width = 8;
	info.map_height = 8;
	info.map_size = info.map_width * info.map_height;
	info.tile_size = 64;
	info.fov = 90;
	info.pa = 90;
	info.px = 150;
	info.py = 400;
	info.pdx = cos(deg_to_rad(info.pa));
	info.pdy = -sin(deg_to_rad(info.pa));
	info.cpx = 0;
	info.cpy = 0.66;
	info.rdx = 0;
	info.rdy = 0;
	info.mlx = mlx_init(info.screen_width, info.screen_height, "cub3D", true);
	return (info);
}

// Draws a line using the bresenheim algorithm
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

// Draws a rectangle
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
	int r,mx,my,mp,dof,side;
	double vx,vy,rx,ry,ra,xo,yo,disV,disH,Tan;; 

	ra = fix_ang(info.pa + info.fov / 2);
	r = 0;
	while (r < info.fov)
	{
		// Check vertical lines
		dof=0; side=0; disV=100000;
		Tan=tan(deg_to_rad(ra));
		if(cos(deg_to_rad(ra))> 0.001){ rx=(((int)info.px>>6)<<6)+64; ry=(info.px-rx)*Tan+info.py; xo= 64; yo=-xo*Tan;}//looking left
		else if(cos(deg_to_rad(ra))<-0.001){ rx=(((int)info.px>>6)<<6) -0.0001; ry=(info.px-rx)*Tan+info.py; xo=-64; yo=-xo*Tan;}//looking right
		else {rx=info.px; ry=info.py; dof=8;}
		
		while(dof<8)
		{
			mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*info.map_width+mx;
			if(mp>0 && mp<info.map_width*info.map_height && worldMap[mp]==1){ dof=8; disV=cos(deg_to_rad(ra))*(rx-info.px)-sin(deg_to_rad(ra))*(ry-info.py);}//hit
			else{ rx+=xo; ry+=yo; dof+=1;}//check next horizontal
		}
		vx=rx; vy=ry;

		// Check horizontal lines
		dof=0; disH=100000;
		Tan=1.0/Tan; 
		if(sin(deg_to_rad(ra))> 0.001){ ry=(((int)info.py>>6)<<6) -0.0001; rx=(info.py-ry)*Tan+info.px; yo=-64; xo=-yo*Tan;}//looking up 
		else if(sin(deg_to_rad(ra))<-0.001){ ry=(((int)info.py>>6)<<6)+64;      rx=(info.py-ry)*Tan+info.px; yo= 64; xo=-yo*Tan;}//looking down
		else{ rx=info.px; ry=info.py; dof=8;}//looking straight left or right
 
		while(dof<8)
		{
			mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*info.map_width+mx;
			if(mp>0 && mp<info.map_width*info.map_height && worldMap[mp]==1){ dof=8; disH=cos(deg_to_rad(ra))*(rx-info.px)-sin(deg_to_rad(ra))*(ry-info.py);}//hit         
			else{ rx+=xo; ry+=yo; dof+=1;}//check next horizontal
		}

		if (disV < disH)
		{
			rx=vx;
			ry=vy;
			disH=disV;
		} //horizontal hit first

		draw_line(image, info.px, info.py, rx, ry, RED); //draw 2d ray

		int ca=fix_ang(info.pa-ra); disH=disH*cos(deg_to_rad(ca)); //fix fisheye 
		int lineH = (info.map_size * 320)/(disH); if(lineH>320){ lineH=320;} //line height and limit
		int lineOff = 160 - (lineH>>1); //line offset
		if (lineH > 0)
			mlx_draw_rect(image, r*8+530,lineOff,8,lineH,RED); //draw the vertical strip
		//draw_line(image, r*8+530,lineOff,r*8+530,lineOff+lineH,BLUE); //draw the vertical line
		//(r*8+530,lineOff);
		//glVertex2i(r*8+530,lineOff+lineH);

		ra = fix_ang(ra - 1);
		r++;
	}
}

// Draws the minimap
void	draw_map(t_info info)
{
	int		x;
	int		y;

	mlx_draw_rect(image, 0, 0, info.map_width * info.tile_size, info.map_height * info.tile_size, BLACK);
	y = 0;
	while (y < info.map_height)
	{
		x = 0;
		while (x < info.map_width)
		{
			if (worldMap[y * info.map_width + x] == 1)
				mlx_draw_rect(image,
					x * info.tile_size + 1, y * info.tile_size + 1,
					info.tile_size - 2, info.tile_size - 2, WHITE);
			else
				mlx_draw_rect(image,
					x * info.tile_size + 1, y * info.tile_size + 1,
					info.tile_size - 2, info.tile_size - 2, DARKGRAY);
			x++;
		}
		y++;
	}
}

// Draws the player
void	draw_player(t_info info)
{
	mlx_draw_rect(image,
		info.px - 2,
		info.py - 2, 5, 5, PURPLE);
	// draw_line(image,
	// 	info.px,
	// 	info.py,
	// 	info.px + info.pdx * (info.tile_size / 2),
	// 	info.py + info.pdy * (info.tile_size / 2), RED);
	printf("px: %f, py: %f, pa: %f\n", info.px, info.py, info.pa);
	draw_line(image, info.px, info.py, info.px + info.pdx * 20, info.py + info.pdy * 20, RED);
}

void	ft_hook(void *param)
{
	t_info	*info;
	mlx_t	*mlx;
	double rotationSpeed = 5; // Adjust the value as needed
	double movementSpeed = 5; // Adjust the value as needed

	info = param;
	mlx = info->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		printf("px: %f, py: %f, pa: %f\n", info->px, info->py, info->pa);
		info->px += info->pdx * movementSpeed;
		info->py += info->pdy * movementSpeed;
		mlx_draw_rect(image, 0, 0, info->screen_width, info->screen_height, BLACK);
		draw_map(*info);
		draw_player(*info);
		draw(*info);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		printf("px: %f, py: %f, pa: %f\n", info->px, info->py, info->pa);
		info->px -= info->pdx * movementSpeed;
		info->py -= info->pdy * movementSpeed;
		mlx_draw_rect(image, 0, 0, info->screen_width, info->screen_height, BLACK);
		draw_map(*info);
		draw_player(*info);
		draw(*info);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		printf("px: %f, py: %f, pa: %f\n", info->px, info->py, info->pa);
		info->pa += rotationSpeed;
		info->pa = fix_ang(info->pa);
		info->pdx = cos(deg_to_rad(info->pa));
		info->pdy = sin(deg_to_rad(info->pa));
		mlx_draw_rect(image, 0, 0, info->screen_width, info->screen_height, BLACK);
		draw_map(*info);
		draw_player(*info);
		draw(*info);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		printf("px: %f, py: %f, pa: %f\n", info->px, info->py, info->pa);
		info->pa -= rotationSpeed;
		info->pa = fix_ang(info->pa);
		info->pdx = cos(deg_to_rad(info->pa));
		info->pdy = sin(deg_to_rad(info->pa));
		mlx_draw_rect(image, 0, 0, info->screen_width, info->screen_height, BLACK);
		draw_map(*info);
		draw_player(*info);
		draw(*info);
	}
}

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
	draw_map(info);
	draw_player(info);
	draw(info);
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
