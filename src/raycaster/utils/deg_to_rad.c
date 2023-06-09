/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deg_to_rad.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 19:57:51 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/18 19:58:14 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	deg_to_rad(int a)
{
	return (a * M_PI / 180.0);
}
