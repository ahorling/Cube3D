/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colours.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 21:49:18 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/20 19:19:37 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H

void	colour_checker(char *string);
int		assemble_colour(int r, int g, int b);
int		get_code(char *string, int skip);
int		get_colour(char **strings, char *id);

#endif