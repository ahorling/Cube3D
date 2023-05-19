/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_image.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 19:58:54 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 19:59:05 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "stop.h"

mlx_image_t	*init_image(mlx_t *mlx, int width, int height)
{
	mlx_image_t	*image;

	image = mlx_new_image(mlx, width, height);
	if (!image)
		stop("Failed to initialize image");
	return (image);
}
