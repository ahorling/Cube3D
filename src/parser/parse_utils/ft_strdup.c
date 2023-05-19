/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 20:00:21 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 20:06:29 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "errors.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		leng;
	char	*dupe;

	i = 0;
	leng = 0;
	while (str[i] != '\0')
	{
		leng++;
		i++;
	}
	i = 0;
	dupe = (char *)malloc((leng + 1) * sizeof(char));
	if (dupe == NULL)
		malloc_error("ft_strdup");
	while (str[i] != '\0')
	{
		dupe[i] = str[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}
