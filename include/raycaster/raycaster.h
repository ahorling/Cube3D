/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:52:54 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 15:27:39 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "MLX42.h"

// Struct with all the info needed for the raycaster
// pa = player angle
// px = player x position
// py = player y position
// pdx = player x direction
// pdy = player y direction
// cpx = camera plane x
// cpy = camera plane y
// rx = ray x position
// ry = ray y position
// ra = ray angle
// rda = ray delta angle
// rdx = ray direction x
// rdy = ray direction y
// pwd = perp wall distance
// s_dist_x = side distance x
// s_dist_y = side distance y
// mspeed = movement speed of the player
// rspeed = rotation speed of the player

typedef struct s_raycaster
{
	mlx_image_t		*background;
	mlx_image_t		*screen;
	int				floor_color;
	int				ceiling_color;
	int				color;
	int				screen_width;
	int				screen_height;
	int				map_width;
	int				map_height;
	int				**map;
	int				tile_size;
	int				map_x;
	int				map_y;
	int				side;
	int				step_x;
	int				step_y;
	int				x;
	int				y;
	double			pa;
	double			px;
	double			py;
	double			pdx;
	double			pdy;
	double			cx;
	double			cpx;
	double			cpy;
	double			d_dist_x;
	double			d_dist_y;
	double			rx;
	double			ry;
	double			ra;
	double			rda;
	double			rdx;
	double			rdy;
	double			pwd;
	double			s_dist_x;
	double			s_dist_y;
	double			mspeed;
	double			rspeed;
	int				pitch;
	int				tex_height;
	int				tex_width;
	int				tex_x;
	int				tex_y;
	int				tex_num;
	int				draw_start;
	int				draw_end;
	double			line_height;
	double			tex_pos;
	double			tex_step;
	double			wall_x;
	mlx_t			*mlx;
	mlx_texture_t	*tex;
}					t_raycaster;

#endif
