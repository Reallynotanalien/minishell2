/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:38:55 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:38:58 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Duplicates string "src" in a new allocated string, and returns a pointer to 
it.*/
char	*ft_strdup(char *src)
{
	int		len;
	char	*copy;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	copy = ft_calloc(sizeof(char), len + 1);
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, src, len);
	return (copy);
}
