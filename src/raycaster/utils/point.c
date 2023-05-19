/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coord.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 14:57:38 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/18 15:25:21 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point	pt(int x, int y)
{
	t_point	out;

	out.x = x;
	out.y = y;
	return (out);
}
