/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 14:34:56 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/17 17:50:59 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "draw_rectangle.h"
#include "raycaster.h"
#include "rectangle.h"

static void	draw_minimap_pixel(t_raycaster rc, int x, int y)
{
	if (rc.map[y][x] == 1)
	{
		draw_rect(rc.screen,
			rect(x * rc.tile_size + 1, y * rc.tile_size + 1,
				rc.tile_size - 2, rc.tile_size - 2), WHITE);
	}
	else
	{
		draw_rect(rc.screen,
			rect(x * rc.tile_size + 1, y * rc.tile_size + 1,
				rc.tile_size - 2, rc.tile_size - 2), DARKGRAY);
	}
}

// Draws a minimap that shows the floor and the walls.
void	draw_map(t_raycaster rc)
{
	int	x;
	int	y;

	draw_rect(rc.screen, rect(0, 0, rc.map_width * rc.tile_size,
			rc.map_height * rc.tile_size), BLACK);
	x = 0;
	while (x < rc.map_width)
	{
		y = 0;
		while (y < rc.map_height)
		{
			draw_minimap_pixel(rc, x, y);
			y++;
		}
		x++;
	}
}
