/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:42:45 by kafortin          #+#    #+#             */
/*   Updated: 2023/12/18 17:33:06 by edufour          ###   ########.fr       */
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
