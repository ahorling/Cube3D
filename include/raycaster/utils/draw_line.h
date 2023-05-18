/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 14:54:36 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/18 15:27:16 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_LINE_H
# define DRAW_LINE_H

# include "point.h"
# include "MLX42.h"

typedef struct s_linehelper
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
	int	x;
	int	y;
}			t_linehelper;

void	draw_line(mlx_image_t *img, t_point c0, t_point c1, int color);

#endif
