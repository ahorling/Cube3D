/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_to_window.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 19:54:49 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 19:57:18 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "stop.h"

// Puts an image on the mlx image.
void	image_to_window(mlx_t *mlx, mlx_image_t *image, int x, int y)
{
	if (mlx_image_to_window(mlx, image, x, y) == -1)
		stop("Failed to put image to window");
}
