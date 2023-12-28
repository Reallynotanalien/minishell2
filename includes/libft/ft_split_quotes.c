/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:03:42 by kafortin          #+#    #+#             */
/*   Updated: 2023/12/20 15:53:03 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "../minishell.h"

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

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	while (str[len] && (((str[len] != '\'' && str[len] != '\"'))
			|| (double_quoted(str, len) || single_quoted(str, len))))
		len++;
	new_str = ft_calloc(len + 1, sizeof(char));
	len = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] != '\'' && str[i] != '\"')
			|| (double_quoted(str, i) || single_quoted(str, i)))
			new_str[len++] = str[i];
		i ++;
	}
	free (str);
	return (new_str);
}

char	*ft_str_malloc_copy(char const *s, char c)
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
	return (str);
}

int	is_quote(char check)
{
	if (check == '\'' ||  check == '\"')
		return (1);
	return (0);
}

// int	count_words(char *str)
// {
// 	int	i;
// 	int	nb_spaces;
// 	int	nb_quotes;

// 	nb_spaces = 0;
// 	nb_quotes = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ' && !is_quote(str[i + 1])
// 			&& (i == 0 || !is_quote(str[i - 1]))
// 			&& !double_quoted(str, i) && ! single_quoted(str, i))
// 			nb_spaces ++;
// 		if (is_quote(str[i] && !double_quoted(str, i) && !single_quoted(str, i)))
// 			nb_quotes++;
// 	}
// 	return (nb_spaces + (nb_quotes / 2));
// }

// //returns the next command's argument as a char *. Splits on spaces
// //except if quoted, and returns an allocated empty char * if there is nothing. Removes unquoted quotes.
// char *split_next_word(char *str, int *index)
// {
// 	char	*new_word;
// 	int		len;

// 	len = 0;
// 	while (str[*index + len] && !(str[*index + len] == ' '
// 		&& !double_quoted(str, *index + len) && !single_quoted(str, *index + len)))
// 		if (!is_quote(str[*index + len]) 
// 			|| double_quoted(str, *index + len) || single_quoted(str, *index + len))
// 		len++;
// 	if (len == 0)
// 		return (ft_calloc(1, 1));
// 	new_word = ft_calloc(len + 1, sizeof(char));
// 	len = 0;
// 	while (str[*index] && !(str[*index] == ' ' && !double_quoted(str, *index) && !single_quoted(str, *index)))
// 	{
// 		if (!is_quote(str[*index]))
// 			new_word[len] = str[*index];
// 		len++;
// 		index++;
// 	}
// 	return (new_word);
// 	//need to make sure *index is ok
// }

/*Allocates (with malloc) and returns a table of char strings
obtained while separating "s" with char "c" acting as a delimiter
(the table must end with NULL).*/
// void	**ft_split_quotes(char const *s, char c)
// {
// 	char	**new_array;
// 	char	*tmp;
// 	int 	nb_words;
// 	int		*i;

// 	nb_words = count_words(s);
// 	if (nb_words == 0)
// 		return (ft_calloc(1, sizeof(char *)));
// 	new_array = ft_calloc(nb_words + 1, sizeof(char *));
// 	i = ft_calloc(1, sizeof(int));
// 	nb_words = 0;
// 	*i = 0;
// 	while (s[*i])
// 		new_array[nb_words++] = split_next_word(s, i);
// 	return (new_array);
	// void	**new_tab;
	// char	*temp;
	// size_t	a;
	// size_t	b;
	// size_t	len;

	// a = 0;
	// b = 0;
	// if (!s)
	// 	return (NULL);
	// temp = ft_strdup((char *)s);
	// if (!temp)
	// 	return (NULL);
	// len = ft_count_words_quotes(temp, c);
	// new_tab = (void **)ft_calloc(sizeof(char *), (len + 1));
	// while (a < len)
	// {
	// 	new_tab[a] = ft_str_malloc_copy((temp + b), c);
	// 	while (temp[b] != '\0' && temp[b] == c)
	// 		b++;
	// 	b += ft_strlen(new_tab[a]);
	// 	new_tab[a] = remove_quotes(new_tab[a]);
	// 	a++;
	// }
	// free(temp);
	// return (new_tab);
// }
