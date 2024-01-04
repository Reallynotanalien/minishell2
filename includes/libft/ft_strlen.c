/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:32:50 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 14:47:10 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Calculates the length of a string.*/
size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	if (!str[0])
		return (0);
	while (str[a] != '\0')
	{
		a++;
	}
	return (a);
}
