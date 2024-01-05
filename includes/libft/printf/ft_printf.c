/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:36:10 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:36:15 by kafortin         ###   ########.fr       */
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
