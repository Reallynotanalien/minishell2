/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:42:45 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:37:56 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Searches for the first occurence of the character "c" in the first "n" number
of bytes of the memory area "*str", and returns a pointer to it.*/
void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*b;
	size_t			a;

	a = 0;
	b = (unsigned char *)str;
	while (n > a)
	{
		if (*b == (unsigned char)c)
			return (b);
		b++;
		a++;
	}
	return (NULL);
}
