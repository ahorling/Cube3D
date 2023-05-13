/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/13 14:09:44 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/13 18:00:58 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# include "MLX42.h"

typedef struct s_info
{
	int		screen_width;
	int		screen_height;
	int		map_width;
	int		map_height;
	int		**map;
	double	cam_plane_x;
	double	cam_plane_y;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	ray_dir_x;
	double	ray_dir_y;
	mlx_t	*mlx;
}			t_info;

#endif
