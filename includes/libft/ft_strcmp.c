/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:12:00 by kafortin          #+#    #+#             */
/*   Updated: 2023/12/21 14:03:52 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
/*Compares between two strings and returns 0 if both are equal, or 1 
if they are not.*/
int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	a;

	a = 0;
	while (((unsigned char)str1[a] != '\0' || (unsigned char)str2[a] != '\0'))
	{
		if ((unsigned char)str1[a] != (unsigned char)str2[a])
			return ((unsigned char)str1[a] - (unsigned char)str2[a]);
		a++;
	}
	return (0);
}
