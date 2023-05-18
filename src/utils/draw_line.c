/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 12:53:42 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/18 15:30:13 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "draw_line.h"
#include "MLX42.h"
#include "point.h"

static void	lh_init(t_linehelper *lh, t_point *p0, t_point *p1)
{
	lh->dx = abs(p1->x - p0->x);
	if (p0->x < p1->x)
		lh->sx = 1;
	else
		lh->sx = -1;
	lh->dy = -abs(p1->y - p0->y);
	if (p0->y < p1->y)
		lh->sy = 1;
	else
		lh->sy = -1;
	lh->err = lh->dx + lh->dy;
	lh->x = p0->x;
	lh->y = p0->y;
}

void	draw_line(mlx_image_t *img, t_point p0, t_point p1, int color)
{
	t_linehelper	lh;

	lh_init(&lh, &p0, &p1);
	while (1)
	{
		mlx_put_pixel(img, lh.x, lh.y, color);
		if ((lh.x == p1.x) && (lh.y == p1.y))
			break ;
		lh.e2 = 2 * lh.err;
		if (lh.e2 >= lh.dy)
		{
			lh.err += lh.dy;
			lh.x += lh.sx;
		}
		if (lh.e2 <= lh.dx)
		{
			lh.err += lh.dx;
			lh.y += lh.sy;
		}
	}
}
