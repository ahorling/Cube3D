/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 16:11:01 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 16:11:13 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *str, int ch, size_t size)
{
	char	*input;
	size_t	i;

	i = 0;
	input = (char *)str;
	while (i < size)
	{
		if (input[i] == ch)
			return (&input[i]);
		i++;
	}
	return (NULL);
}
