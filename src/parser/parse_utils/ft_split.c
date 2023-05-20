/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 15:30:27 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/20 17:42:13 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "errors.h"
#include "ft_memchr.h"
#include "ft_substr.h"
#include "ft_strlen.h"

// static char	**freesplits(char **table, int tableindex)
// {
// 	int	i;

// 	i = tableindex;
// 	while (i >= 0)
// 	{
// 		free(table[i]);
// 		i--;
// 	}
// 	free(table);
// 	return (NULL);
// }

static int	numofsplits(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (i == ft_strlen(s))
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && i != ft_strlen(s) - 1)
			count++;
		i++;
	}
	return (count + 1);
}

static char	*pullstring(char *s, char c)
{
	int		i;
	int		skip;
	int		length;
	char	*pulledstring;

	i = 0;
	while (s[i] == c)
		i++;
	skip = i;
	while (s[i] != c && s[i] != '\0')
		i++;
	length = i;
	pulledstring = (ft_substr(s, skip, length - skip));
	return (pulledstring);
}

char	**ft_split(char *s, char c)
{
	int		entries;
	int		i;
	char	**table;

	i = 0;
	if (s == NULL)
		return (NULL);
	entries = numofsplits(s, c);
	table = (char **)malloc((entries + 1) * sizeof(char *));
	if (table == NULL)
		malloc_error("ft_split");
	while (i < entries)
	{
		table[i] = pullstring(s, c);
		if (table[i] == NULL)
			malloc_error("ft_split, after pullsting");
		while (*s == c)
			s++;
		s = ft_memchr(s, c, ft_strlen(s));
		i++;
	}
	table[i] = NULL;
	return (table);
}