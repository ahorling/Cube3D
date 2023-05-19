/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_pixel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 12:08:46 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 19:32:47 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

// Puts a pixel on the image.
void	put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	if (x < 0 || x >= (int)image->width || y < 0 || y >= (int)image->height)
		return ;
	mlx_put_pixel(image, x, y, color);
}
