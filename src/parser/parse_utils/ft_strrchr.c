/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:27:39 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/18 17:40:35 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_strchr.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*input;

	input = (char *)str;
	if (ft_strchr(str, c) == NULL)
		return (NULL);
	while (*input != '\0')
		input++;
	while (*input != c)
		input--;
	return (input);
}
