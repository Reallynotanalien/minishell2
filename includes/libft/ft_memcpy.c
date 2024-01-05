/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:33:20 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:38:03 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Copies "n" number of characters from memory area "src" to memory area 
"dest".*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	a;

	a = 0;
	if (!dest && !src)
		return (NULL);
	while (a < n)
	{
		((char *)dest)[a] = ((char *)src)[a];
		a++;
	}
	((char *)dest)[a] = '\0';
	return (dest);
}
