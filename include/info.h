/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/13 14:09:44 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/16 14:34:48 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# include "MLX42.h"

// Struct with all the info needed for the raycaster
// pa = player angle
// px = player x position
// py = player y position
// pdx = player x direction
// pdy = player y direction
// cpx = camera plane x
// cpy = camera plane y
// rdx = ray direction x
// rdy = ray direction y
typedef struct s_info
{
	int		screen_width;
	int		screen_height;
	int		map_width;
	int		map_height;
	int		map_size;
	int		**map;
	int		tile_size;
	double	fov;
	double	pa;
	double	px;
	double	py;
	double	pdx;
	double	pdy;
	double	cpx;
	double	cpy;
	double	rx;
	double	ry;
	double	ra;
	double	rda;
	double	rdx;
	double	rdy;
	mlx_t	*mlx;
}			t_info;

#endif
