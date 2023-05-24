/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_map.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:32:23 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/20 21:51:19 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_MAP_H
# define FIND_MAP_H

# include <stdbool.h>

# ifndef VALID_MAP_CHAR
# define VALID_MAP_CHAR	"012NSWE' '"
# endif


bool	valid_line(char *string);
int		find_map(char **strings);

#endif
