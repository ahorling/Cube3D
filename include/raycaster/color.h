/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/13 18:43:15 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/16 19:03:52 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

// ENUM with color values
typedef enum e_color
{
	TRANSPARENT = 0x00000000,
	TRANSLUCENT = 0x0000007F,
	BLACK = 0x000000FF,
	GRAY = 0x808080FF,
	WHITE = 0xFFFFFFFF,
	RED = 0xFF0000FF,
	GREEN = 0x00FF00FF,
	BLUE = 0x0000FFFF,
	YELLOW = 0xFFFF00FF,
	PURPLE = 0xFF00FFFF,
	CYAN = 0x00FFFFFF,
	ORANGE = 0xFFA500FF,
	PINK = 0xFFC0CBFF,
	BROWN = 0xA52A2AFF,
	SKYBLUE = 0x87CEEBFF,
	LIGHTGRAY = 0xBBBBBBFF,
	LIGHTBLUE = 0xADD8E6FF,
	LIGHTPINK = 0xFFB6C1FF,
	LIGHTGREEN = 0x90EE90FF,
	LIGHTYELLOW = 0xFFFFE0FF,
	LIGHTORANGE = 0xFFDAB9FF,
	LIGHTPURPLE = 0xE6E6FAFF,
	LIGHTCYAN = 0xE0FFFFFF,
	LIGHTBROWN = 0xD2B48CFF,
	LIGHTSKYBLUE = 0x87CEFAFF,
	DARKGRAY = 0x404040FF,
	DARKBLUE = 0x00008BFF,
	DARKGREEN = 0x006400FF,
	DARKRED = 0x8B0000FF,
	DARKORANGE = 0xFF8C00FF,
	DARKPURPLE = 0x800080FF,
	DARKCYAN = 0x008B8BFF,
	DARKPINK = 0xFF1493FF,
	DARKYELLOW = 0xBDB76BFF,
	DARKBROWN = 0x8B4513FF,
	DARKSKYBLUE = 0x00BFFFFF,
	PANTONE448C = 0x4A412AFF,
	MAUVE = 0xE0B0FFFF,
}				t_color;

#endif
