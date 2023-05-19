/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colours.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 21:30:08 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 21:56:24 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_atoi.h"
#include "ft_substr.h"

#include <stdio.h>

int	get_code(char *string, int skip)
{
	int		start;
	int		end;
	int		ret;
	char	*temp;

	start = 2;
	end = start;
	while (string[end] != ',')
	{
		end++;
		if (string[end] == ',' && skip > 0)
		{
			end++;
			start = end;
			skip--;
		}
	}
	temp = ft_substr(string, start, end - start);
	ret = (int)ft_atoi(temp);
	printf("%d\n", ret);
	free(temp);
	return (ret);
}

// F 20,100,5
// 0123456789