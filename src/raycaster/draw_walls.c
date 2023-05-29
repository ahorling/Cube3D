/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 20:05:44 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/29 13:05:00 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"
#include "correct_color.h"
#include "put_pixel.h"
#include "raycaster.h"

// Calculate wall height, draw start and end positions for the wall.
// Calculate the step size and x position on the texture.
void	prepare_for_drawing(t_raycaster *rc)
{
	rc->line_height = (int)(rc->screen_height / rc->pwd);
	rc->draw_start = -rc->line_height / 2 + rc->screen_height / 2 + rc->pitch;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + rc->screen_height / 2 + rc->pitch;
	if (rc->draw_end >= rc->screen_height)
		rc->draw_end = rc->screen_height - 1;
	if (rc->side == 0)
		rc->wall_x = rc->py + rc->pwd * rc->rdy;
	else
		rc->wall_x = rc->px + rc->pwd * rc->rdx;
	rc->wall_x -= floor((rc->wall_x));
}

// Set the texture to use for the wall depending on the side.
// Then set the x position on the texture.
// static void	prepare_for_texture(t_raycaster *rc)
void	prepare_for_texture(t_raycaster *rc)
{
	if (rc->side == 0 && rc->rdx > 0)
		rc->tex_num = 0;
	if (rc->side == 0 && rc->rdx < 0)
		rc->tex_num = 1;
	if (rc->side == 1 && rc->rdy > 0)
		rc->tex_num = 2;
	if (rc->side == 1 && rc->rdy < 0)
		rc->tex_num = 3;
	rc->tex = rc->textures[rc->tex_num];
	rc->tex_x = (int)(rc->wall_x * (double)(rc->tex->width));
	if (rc->side == 0 && rc->rdx > 0)
		rc->tex_x = rc->tex->width - rc->tex_x - 1;
	if (rc->side == 1 && rc->rdy < 0)
		rc->tex_x = rc->tex->width - rc->tex_x - 1;
	rc->tex_step = (double)rc->tex->height / (double)rc->line_height;
	rc->tex_pos = (rc->draw_start - rc->pitch - rc->screen_height / 2
			+ rc->line_height / 2) * rc->tex_step;
}

// Draws the walls on the screen image.
void	draw_textured_walls(t_raycaster *rc)
{
	rc->y = 0;
	while (rc->y < rc->draw_start)
	{
		put_pixel(rc->screen, rc->x, rc->y, TRANSPARENT);
		rc->y++;
	}
	while (rc->y < rc->draw_end)
	{
		rc->tex_y = (int)rc->tex_pos;
		rc->tex_pos += rc->tex_step;
		rc->color = correct_color(
				&rc->tex->pixels[(rc->tex->width * rc->tex_y
					+ (rc->tex->width - rc->tex_x - 1)) * 4]);
		put_pixel(rc->screen, rc->x, rc->y, rc->color);
		rc->y++;
	}
	while (rc->y < rc->screen_height)
	{
		put_pixel(rc->screen, rc->x, rc->y, TRANSPARENT);
		rc->y++;
	}
}
