/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_whitespaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:54:34 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/16 15:01:32 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Removes whitespaces before and after a string.
char	*ft_strtrim_whitespaces(char *str)
{
	int		i_start;
	int		i_end;
	char	*str_cpy;

	i_start = 0;
	while (str[i_start] && (ft_iswhitespace(str[i_start])))
		i_start++;
	i_end = ft_strlen(str) - 1;
	while (str[i_end] && (ft_iswhitespace(str[i_end])))
		i_end--;
	str_cpy = ft_substr(str, i_start, i_end - i_start + 1);
	free (str);
	return (str_cpy);
}
