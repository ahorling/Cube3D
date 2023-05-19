/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 20:08:36 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 20:09:13 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_WALLS_H
# define DRAW_WALLS_H

# include "raycaster.h"

void	prepare_for_drawing(t_raycaster *rc);
void	prepare_for_texture(t_raycaster *rc);
void	draw_textured_walls(t_raycaster *rc);

#endif
