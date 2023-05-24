/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 16:59:51 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/24 19:24:04 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# ifndef ERROR
# define ERROR STDERR_FILENO
# endif

void	file_error(int error);
void	map_error(int error);
void	colour_error(int error);
void	texture_error(int error);
void	argument_error(void);
void	file_path_error(int error);
void	read_error(void);
void	malloc_error(char *string);

#endif