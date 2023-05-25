/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_background.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 19:29:10 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/25 19:31:46 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "draw_rectangle.h"
#include "raycaster.h"

// Sets the background layer for floor and ceiling.
void	set_background(t_raycaster rc)
{
	draw_rect(rc.background,
		rect(0, 0, rc.screen_width, rc.screen_height / 2 + rc.pitch),
		rc.ceiling_color);
	draw_rect(rc.background,
		rect(0, rc.screen_height / 2 + rc.pitch,
			rc.screen_width, rc.screen_height / 2 - rc.pitch),
		rc.floor_color);
}
