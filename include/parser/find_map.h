/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_map.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:32:23 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/29 13:06:52 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_MAP_H
# define FIND_MAP_H

# include <stdbool.h>

# ifndef VALID_MAP_CHAR
#  define VALID_MAP_CHAR	"012NSWE' '"
# endif

bool	valid_line(char *string);
int		find_map(char **strings);

#endif
