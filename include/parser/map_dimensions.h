/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_dimensions.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 19:46:50 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/26 11:01:22 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_DIMENSIONS_H
# define MAP_DIMENSIONS_H

# include "info.h"

void	get_dimensions(t_info *info, char **map, int mapstart);
void	set_dimensions(t_info *info, char **map);

#endif