/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/13 18:43:15 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/13 18:49:00 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

// ENUM with color values
typedef enum e_color
{
	TRANSPARENT = 0x00000000,
	BLACK = 0x000000FF,
	WHITE = 0xFFFFFFFF,
	RED = 0xFF0000FF,
	GREEN = 0x00FF00FF,
	BLUE = 0x0000FFFF,
	YELLOW = 0xFFFF00FF,
	PURPLE = 0xFF00FFFF,
	CYAN = 0x00FFFFFF,
	ORANGE = 0xFFA500FF,
	PINK = 0xFFC0CBFF,
	GREY = 0x808080FF,
	BROWN = 0xA52A2AFF,
	SKYBLUE = 0x87CEEBFF,
	DARKGRAY = 0x404040FF,
}				t_color;

#endif
