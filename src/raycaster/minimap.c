/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 14:34:56 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/25 20:01:42 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "draw_line.h"
#include "draw_rectangle.h"
#include "point.h"
#include "raycaster.h"
#include "rectangle.h"

// Draws the player on the minimap with a direction vector.
static void	draw_player(t_raycaster rc)
{
	draw_line(rc.minimap, pt(rc.px * rc.tile_size, rc.py * rc.tile_size),
		pt(rc.px * rc.tile_size + rc.pdx * (rc.tile_size / 2),
			rc.py * rc.tile_size + rc.pdy * (rc.tile_size / 2)), RED);
	draw_line(rc.minimap, pt(rc.px * rc.tile_size - rc.pdy * (rc.tile_size / 4),
			rc.py * rc.tile_size + rc.pdx * (rc.tile_size / 4)),
		pt(rc.px * rc.tile_size + rc.pdy * (rc.tile_size / 4),
			rc.py * rc.tile_size - rc.pdx * (rc.tile_size / 4)), GREEN);
}

// Draws a tile on the minimap.
static void	draw_map_tile(t_raycaster rc, int x, int y)
{
	if (rc.map[y][x] == 1)
	{
		draw_rect(rc.minimap,
			rect(x * rc.tile_size + 1, y * rc.tile_size + 1,
				rc.tile_size - 2, rc.tile_size - 2), WHITE);
	}
	else if (rc.map[y][x] == 0)
	{
		draw_rect(rc.minimap,
			rect(x * rc.tile_size + 1, y * rc.tile_size + 1,
				rc.tile_size - 2, rc.tile_size - 2), DARKGRAY);
	}
	else
	{
		draw_rect(rc.minimap,
			rect(x * rc.tile_size, y * rc.tile_size,
				rc.tile_size, rc.tile_size), TRANSPARENT);
	}
}

// Draws a minimap that shows the floor and the walls.
void	draw_map(t_raycaster rc)
{
	int	x;
	int	y;

	if (rc.tile_size == -1)
	{
		draw_rect(rc.minimap, rect(0, 0, rc.map_width * rc.tile_size,
				rc.map_height * rc.tile_size), TRANSPARENT);
		return ;
	}
	draw_rect(rc.minimap, rect(0, 0, rc.map_width * rc.tile_size,
			rc.map_height * rc.tile_size), BLACK);
	x = 0;
	while (x < rc.map_width)
	{
		y = 0;
		while (y < rc.map_height)
		{
			draw_map_tile(rc, x, y);
			y++;
		}
		x++;
	}
	draw_player(rc);
}
