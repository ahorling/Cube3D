/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 16:59:51 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/18 21:08:38 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

void	argument_error(void);
void	file_path_error(int error);
void	read_error(void);
void	malloc_error(char *string);

#endif