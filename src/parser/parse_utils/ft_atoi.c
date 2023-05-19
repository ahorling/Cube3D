/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 21:45:42 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 21:48:16 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "errors.h"

int	error_check(const char *str)
{
	int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (str[i]);
	return (0);
}

size_t	ft_atoi(const char *str)
{
	size_t	value;
	int		i;
	int		neg;

	i = 0;
	value = 0;
	neg = 1;
	if (error_check(str) != 0)
		colour_error(1);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + str[i] - '0';
		i++;
	}
	return (value * neg);
}