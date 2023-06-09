/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 18:31:15 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/24 17:33:24 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_H
# define MOVEMENT_H

# include "raycaster.h"

void	rotate_player(t_raycaster *rc, double rot);
void	movement(t_raycaster *rc);

#endif
