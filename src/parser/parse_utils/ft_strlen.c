/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 20:20:07 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/18 20:20:53 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}