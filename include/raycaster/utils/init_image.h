/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_image.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 19:59:30 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 19:59:44 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_IMAGE_H
# define INIT_IMAGE_H

# include "MLX42.h"

mlx_image_t	*init_image(mlx_t *mlx, int width, int height);

#endif
