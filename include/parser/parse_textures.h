/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:28:30 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 20:33:25 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TEXTURES_H
# define PARSE_TEXTURES_H

#include <stdbool.h>

typedef struct s_metainfo
{
	bool	floor;
	bool	ceiling;
	bool	*north_texture;
	bool	*east_texture;
	bool	*south_texture;
	bool	*west_texture;
} 			t_metainfo;

char	**get_textures(char **string, t_info *info);

#endif
