/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:52:54 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/17 17:48:47 by fholwerd      ########   odam.nl         */
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
	double		pa;
	double		px;
	double		py;
	double		pdx;
	double		pdy;
	double		cpx;
	double		cpy;
	double		rx;
	double		ry;
	double		ra;
	double		rda;
	double		rdx;
	double		rdy;
	mlx_t		*mlx;
}				t_raycaster;

#endif
