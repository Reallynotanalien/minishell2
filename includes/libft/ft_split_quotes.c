/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:03:42 by kafortin          #+#    #+#             */
/*   Updated: 2023/11/23 17:01:11 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*Returns yes if the character is a double quote.*/
int	is_double_quotee(char c)
{
	if (c == '"')
		return (1);
	return (0);
}

/*Iterates until it finds another double quote character.*/
int	iterate_until_quotes_are_closedd(char *line, int end)
{
	while (line[end + 1] && !is_double_quotee(line[end + 1]))
		end++;
	// if (!ft_iswhitespace(line[end + 1]))
	// 	return (end);
	return (end + 1);
}

/*Counts the number of words in a pointed string, using a char delimitator.*/
size_t	ft_count_words_quotes(char const *s, char sep)
{
	size_t	l;
	size_t	words;
	char	*str;

	l = 0;
	words = 0;
	if (ft_strlen(s) == 0)
		return (0);
	if (sep == '\0')
		return (1);
	str = ft_strtrim(s, &sep);
	if (!str)
		return (0);
	while (str[l])
	{
		while (str[l] && str[l] != sep)
		{
			if (str[l] && str[l] == '"')
				l = iterate_until_quotes_are_closedd(str, l);
			l++;
		}
		while (str[l] && str[l] == sep)
			l++;
		words++;
	}
	free(str);
	return (words);
}

static char	*ft_str_malloc_copy(char const *s, char c)
{
	size_t	a;
	size_t	b;
	size_t	d;
	char	*str;

	a = 0;
	b = 0;
	while (s[a] != '\0' && s[a] == c)
		a++;
	while (s[a] != '\0' && s[a] != c)
	{
		d = 0;
		if (s[a] == '"')
			d = iterate_until_quotes_are_closedd((char *)s, a);
		a += d;
		b += d;
		a++;
		b++;
		if (s[a - 1] == c)
			a -= 1;
	}
	str = ft_substr(s, (a - b), b);
	str = ft_strtrim(str, &c);
	return (str);
}

/*Allocates (with malloc) and returns a table of char strings
obtained while separating "s" with char "c" acting as a delimiter
(the table must end with NULL).*/
void	**ft_split_quotes(char const *s, char c)
{
	void	**tab;
	char	*temp;
	size_t	a;
	size_t	b;
	size_t	len;

	a = 0;
	b = 0;
	if (!s)
		return (NULL);
	temp = ft_strdup((char *)s);
	if (!temp)
		return (NULL);
	len = ft_count_words_quotes(temp, c);
	printf("%zu\n", len);
	tab = (void **)ft_calloc(sizeof(char *), (len + 1));
	while (a < len)
	{
		tab[a] = ft_str_malloc_copy((temp + b), c);
		while (temp[b] != '\0' && temp[b] == c)
			b++;
		b += ft_strlen(tab[a]);
		a++;
	}
	free(temp);
	return (tab);
}
