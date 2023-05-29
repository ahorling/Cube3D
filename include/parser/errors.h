/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 16:59:51 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/29 13:06:43 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# ifndef ERROR
#  define ERROR STDERR_FILENO
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