/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_texture.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 20:00:39 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 20:00:46 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "stop.h"

mlx_texture_t	*load_texture(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		stop("Failed to load texture");
	return (texture);
}
