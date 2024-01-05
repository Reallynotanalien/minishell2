/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:03:54 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:39:17 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc) and returns a new char string from string "s", 
starting from "start" and for "len" number of characters.*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i_s;
	size_t	i_sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	sub = ft_calloc(sizeof(char), len + 1);
	if (!sub)
		return (NULL);
	i_sub = 0;
	i_s = start;
	while (s[i_s + i_sub] && i_sub < len)
	{
		sub[i_sub] = s[i_s + i_sub];
		i_sub++;
	}
	sub[i_sub] = '\0';
	return (sub);
}
