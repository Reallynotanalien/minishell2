/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:08:57 by edufour           #+#    #+#             */
/*   Updated: 2023/12/18 17:28:21 by edufour          ###   ########.fr       */
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
