/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rectangle.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 14:50:09 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/17 14:58:02 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECTANGLE_H
# define RECTANGLE_H

typedef struct s_rectangle
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rectangle;

t_rectangle	rect(int x, int y, int width, int height);

#endif
