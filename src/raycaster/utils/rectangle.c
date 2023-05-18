/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rectangle.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 14:55:45 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/17 14:56:19 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rectangle.h"

// Creates a rectangle struct.
t_rectangle	rect(int x, int y, int width, int height)
{
	t_rectangle	out;

	out.x = x;
	out.y = y;
	out.width = width;
	out.height = height;
	return (out);
}
