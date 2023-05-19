/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_to_window.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 19:55:30 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 19:55:40 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_TO_WINDOW_H
# define IMAGE_TO_WINDOW_H

# include "MLX42.h"

void	image_to_window(mlx_t *mlx, mlx_image_t *image, int x, int y);

#endif
