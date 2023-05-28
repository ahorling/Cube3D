/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/13 14:09:44 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/28 12:22:31 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

typedef struct s_info
{
	int		floor_color;
	int		ceiling_color;
	char	*north_texture;
	char	*east_texture;
	char	*south_texture;
	char	*west_texture;
	char	player_direction;
	int		player_x;
	int		player_y;
	int		map_width;
	int		map_height;
	int		**map;
	int		mapstart;
	int		maplen;
} 			t_info;

#endif
