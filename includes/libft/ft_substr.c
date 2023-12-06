/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:03:54 by kafortin          #+#    #+#             */
/*   Updated: 2023/12/03 20:09:23 by edufour          ###   ########.fr       */
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
