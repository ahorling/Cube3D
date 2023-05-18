/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_rectangle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 14:43:05 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/17 17:33:15 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "rectangle.h"

// Draws a rectangle on the image.
void	draw_rect(mlx_image_t *image, t_rectangle rec, uint32_t color)
{
	int32_t	i;
	int32_t	j;

	i = rec.x;
	while (i < rec.width + rec.x)
	{
		j = rec.y;
		while (j < rec.height + rec.y)
		{
			mlx_put_pixel(image, i, j, color);
			j++;
		}
		i++;
	}
}
