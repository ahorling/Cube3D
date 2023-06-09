/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 18:29:46 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/29 13:07:25 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "info.h"

void	free_info(t_info *info);
t_info	*parse_input(int argc, char **argv);

#endif