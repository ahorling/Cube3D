/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:52:54 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/18 18:19:46 by fholwerd      ########   odam.nl         */
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
// s_dist_x = side distance x
// s_dist_y = side distance y
// mspeed = movement speed of the player
// rspeed = rotation speed of the player

typedef struct s_raycaster
{
	mlx_image_t	*screen;
	int			floor_color;
	int			ceiling_color;
	int			screen_width;
	int			screen_height;
	int			map_width;
	int			map_height;
	int			**map;
	int			tile_size;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		pa;
	double		px;
	double		py;
	double		pdx;
	double		pdy;
	double		cx;
	double		cpx;
	double		cpy;
	double		d_dist_x;
	double		d_dist_y;
	double		rx;
	double		ry;
	double		ra;
	double		rda;
	double		rdx;
	double		rdy;
	double		s_dist_x;
	double		s_dist_y;
	double		mspeed;
	double		rspeed;
	mlx_t		*mlx;
}				t_raycaster;

#endif
