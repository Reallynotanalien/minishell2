/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:03:42 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/15 15:57:34 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_split(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i + 1);
}

static size_t	nb_words(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if ((i > 0 && s[i] == c && s[i - 1] != c)
			|| (s[i + 1] == '\0' && s[i] != c))
			nb++;
		i++;
	}
	return (nb);
}

static char	**no_memory_leaks(char **free_tab)
{
	size_t	i;

	i = 0;
	while (free_tab[i])
	{
		if (free_tab[i])
			free(free_tab[i]);
		i++;
	}
	if (free_tab)
		free(free_tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i_s;
	size_t	i_tab;

	if (!s)
		return (NULL);
	tab = (char **)ft_calloc(nb_words(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i_s = 0;
	i_tab = 0;
	while (i_tab < nb_words(s, c))
	{
		while (s[i_s] == c)
			i_s++;
		tab[i_tab] = ft_substr(s, i_s, size_split(&s[i_s], c) - 1);
		if (!tab[i_tab])
			return (no_memory_leaks(tab));
		i_s += size_split(&s[i_s], c);
		i_tab++;
	}
	tab[i_tab] = NULL;
	return (tab);
}
