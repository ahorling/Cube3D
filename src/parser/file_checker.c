/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:13:25 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/20 18:36:21 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "errors.h"
#include "ft_strcmp.h"
#include "ft_strrchr.h"

#include <stdio.h>

int	check_dots(char *string)
{
	int	dots;
	int	i;

	i = 0;
	dots = 0;
	while(string[i] != '\0')
	{
		if (string[i] == '.')
			dots++;
		i++;
	}
	if (dots > 0)
		return (0);
	return (1);
}

void	check_file(char *path)
{
	char	*temp;
	int		error;
	int		file;
	char	buf[1];

	error = check_dots(path);
	if (error == 1)
		file_path_error(-1);
	error = 0;
	temp = ft_strrchr(path, '.');
	error = ft_strcmp(".cub", temp);
	if (error != 0)
		file_path_error(1);
	file = open(path, O_RDONLY);
	if (file == -1)
		file_path_error(2);
	error = read(file, buf, 1);
	if (error == 0)
		file_path_error(3);
	close(file);
}
