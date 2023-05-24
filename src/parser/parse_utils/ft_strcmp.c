/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:41:55 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/18 19:23:58 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *string1, char *string2)
{
	int	i;

	i = 0;
	if (!string1 || !string2)
		return (-1);
	while (string1[i] != '\0')
	{
		if (string1[i] - string2[i] == 0)
			i++;
		else
			return (string1[i] - string2[i]);
	}
	if (string2[i] != '\0')
		return (string2[i]);
	else
		return (0);
}
