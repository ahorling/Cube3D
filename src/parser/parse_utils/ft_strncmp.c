/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 20:26:37 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/19 20:26:44 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned char	uc1;
	unsigned char	uc2;

	uc1 = '\0';
	uc2 = '\0';
	while (n > 0)
	{
		uc1 = (unsigned char)*s1;
		uc2 = (unsigned char)*s2;
		if (uc1 == '\0' || uc1 != uc2)
			return (uc1 - uc2);
		s1++;
		s2++;
		n--;
	}
	return (uc1 - uc2);
}
