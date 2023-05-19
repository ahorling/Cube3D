/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 16:11:43 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 16:12:23 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMCHR_H
# define FT_MEMCHR_H

# include <unistd.h>

void	*ft_memchr(const void *str, int ch, size_t size);

#endif