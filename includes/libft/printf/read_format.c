/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:37:04 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:37:06 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	read_format(int fd, const char *format, va_list argptr)
{
	int	i;
	int	nb_char;

	i = 0;
	nb_char = 0;
	while (format)
	{
		if (format[i] == '%' && format[i + 1])
		{
			if (ft_strchr("diucsphH%", format[i + 1]) != 0)
			{
				nb_char += print_arg(fd, argptr, format[i + 1]);
				i++;
			}
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			nb_char++;
			i++;
		}
	}
	return (nb_char);
}
