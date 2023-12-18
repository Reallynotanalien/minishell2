/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:57:51 by edufour           #+#    #+#             */
/*   Updated: 2023/12/18 18:23:56 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf(int fd, const char *format, ...)
{
	va_list	argptr;
	int		nb_char;
	int		i;

	i = 0;
	nb_char = 0;
	va_start(argptr, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format [i + 1])
			{
				i++;
				nb_char += print_arg(fd, argptr, format[i]);
			}
		}
		else
			nb_char += write(fd, format + i, 1);
		i++;
	}
	va_end(argptr);
}
