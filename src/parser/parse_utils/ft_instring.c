/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_instring.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 20:44:40 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/20 21:18:45 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include <stdio.h>

bool	ft_instring(char c, char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (true);
		i++;
	}
	return (false);
}
