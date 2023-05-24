/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 20:15:36 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 20:35:19 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "errors.h"
#include "info.h"
#include "ft_strdup.h"
#include "parse_textures.h"
#include "parse_map.h"
#include "get_next_line.h"

#include <stdio.h>

int	count_lines(char *path)
{
	char	*line;
	int		fd;
	int		count;
	int		ret;

	ret = 1;
	count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		file_path_error(2);
	while (ret != 0)
	{
		ret = (get_next_line(fd, &line));
		if (ret == -1)
			read_error();
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

char	**get_contents(char *path)
{
	char	*line;
	char	**contents;
	int		fd;
	int		count;
	int		ret;

	ret = 1;
	count = count_lines(path);
	contents = malloc((count + 1) * sizeof(char *));
	count = 0;
	if (!contents)
		malloc_error("get_contents");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		file_path_error(2);
	while (ret != 0)
	{
		ret = (get_next_line(fd, &line));
		contents[count] = ft_strdup(line);
		count++;
		free(line);
	}
	close(fd);
	contents[count] = NULL;
	return (contents);
}

void	initialize_info(t_info *info, char *path)
{
	char	**filecontents;
	int		i;

	i = 0;
	filecontents = get_contents(path);
	get_textures(filecontents, info);
	get_map(info, filecontents);
	free(filecontents);
}
