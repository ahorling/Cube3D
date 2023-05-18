/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_lines.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 20:30:26 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/18 22:00:28 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "errors.h"
#include "ft_strjoin.h"

#include <stdio.h>

static bool	contains_newline(char *string)
{
	int	i;

	i = 0;
	if (string == NULL)
		return (false);
	while (string[i] != '\0')
	{
		if (string[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

static char	*read_file(int fd)
{
	char	*fulltext;
	char	*temp;
	char	buf[2];
	int		error;

	temp = malloc(sizeof(char) * 1);
	if (!temp)
		malloc_error("read_file");
	error = read(fd, temp, 1);
	if (error < 1)
		read_error();
	while (error > 0)
	{
		error = read(fd, buf, 1);
		if (error < 0)
			read_error();
		buf[1] = '\0';
		if (error != 0)
		{
			fulltext = ft_strjoin(temp, buf);
			free(temp);
			temp = fulltext;
		}
	}
	exit(0);
}

static char	*pull_line(char *string, int skip)
{
	char	*line;
	int		i;
	int		j;
	
	i = skip;
	j = skip;
	while (string[i] != '\n' && string[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		malloc_error("pull_line");
	while (j <= i)
	{
		line[j] = string[j];
		j++;
	}
	return (line);
}

static char	**split_buf(char *string)
{
	int		i;
	int		j;
	char 	*line;
	char	**table;

	i = 0;
	j = 0;
	table = malloc(sizeof(char*));
	while (string[i])
	{
		while (string[i] == '\n')
			i++;
		line = pull_line(string, i);
		j++;

		while (string[i] != '\n')
			i++;
	}
}

char	**get_lines(char *path)
{
	char	**lines;
	char	*buf;
	int		file;

	file = open(path, O_RDONLY);
	if (file < 0)
		file_path_error(2);
	buf = read_file(file);
	lines = split_lines(buf);
	exit(0);
}