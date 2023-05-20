/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:28:40 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/20 20:44:18 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *str, int c)
{
	char	*input;

	input = (char *)str;
	while (*input != '\0')
	{
		if (*input == (char)c)
			return (input);
		input++;
	}
	if ((char)c == '\0')
		return (input);
	return (NULL);
}
