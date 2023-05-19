/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 19:23:25 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 20:03:48 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "errors.h"
#include "ft_strlen.h"
#include "get_next_line_utils.h"

static int	contains_newline(char *string)
{
	size_t	i;

	i = 0;
	if (string == NULL)
		return (0);
	while (string[i] != '\0')
	{
		if (string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	fill_buffer(int fd, char **buffer)
{
	int		file;
	char	*filler;

	filler = (char *)malloc((100 + 1) * sizeof(char));
	if (!filler)
		malloc_error("fill_buffer");
	file = 1;
	while (contains_newline(*buffer) == 0 && file > 0)
	{
		file = read(fd, filler, 100);
		if (file < 0)
			read_error();
		filler[file] = '\0';
		*buffer = add_to_buffer(*buffer, filler);
		if (*buffer == NULL)
			return (-1);
	}
	free(filler);
	filler = NULL;
	if (file > 0)
		file = 1;
	return (file);
}

static char	*pull_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		malloc_error("pull_line");
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*edit_buffer(char *buffer)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] != '\0')
		i++;
	len = ft_strlen(buffer);
	while (buffer[i] != '\0' && i < len)
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	return (buffer);
}

int	get_next_line(int fd, char **line)
{
	static char	*buffer;
	int			return_value;

	if (fd < 0 || !line || fd > 1024)
		return (-1);
	return_value = fill_buffer(fd, &buffer);
	if (return_value == -1)
	{
		*line = NULL;
		return (-1);
	}
	*line = pull_line(buffer);
	if (!*line)
		return (-1);
	buffer = edit_buffer(buffer);
	if (return_value == 0 && buffer != NULL)
	{
		free(buffer);
		buffer = NULL;
	}
	return (return_value);
}