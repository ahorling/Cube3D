/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_rectangle.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 14:54:46 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/17 14:55:20 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_RECTANGLE_H
# define DRAW_RECTANGLE_H

#include "MLX42.h"
#include "rectangle.h"

void	draw_rect(mlx_image_t *image, t_rectangle rec, uint32_t color);

#endif
