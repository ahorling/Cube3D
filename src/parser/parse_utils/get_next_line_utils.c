/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 19:24:55 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 20:04:36 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_strdup.h"
#include "ft_strjoin.h"

char	*add_to_buffer(char *buffer, char *filler)
{
	char	*new_buffer;

	if (!buffer && !filler)
		return (NULL);
	if (buffer == NULL)
		return (ft_strdup(filler));
	else
		new_buffer = ft_strjoin(buffer, filler);
	if (new_buffer == NULL)
		return (NULL);
	free(buffer);
	buffer = NULL;
	return (new_buffer);
}