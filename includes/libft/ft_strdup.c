/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:12:46 by kafortin          #+#    #+#             */
/*   Updated: 2023/11/29 16:28:29 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Duplicates string "src" in a new allocated string, and returns a pointer to 
it.*/
char	*ft_strdup(char *src)
{
	char	*ptr;

	if (!src)
		return (NULL);
	ptr = malloc(ft_strlen(src) + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, src, ft_strlen(src) + 1);
	ptr[ft_strlen(src)] = '\0';
	return (ptr);
}
