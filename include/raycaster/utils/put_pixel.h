/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_pixel.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 12:10:32 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 12:10:43 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_PIXEL_H
# define PUT_PIXEL_H

# include "MLX42.h"

void	put_pixel(mlx_image_t *image, int x, int y, uint32_t color);

#endif
