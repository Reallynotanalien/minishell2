/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:36:38 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:36:40 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_int_char(int fd, int argument, char identifier)
{
	int	sign;

	sign = 0;
	if (argument < 0 && argument != INT_MIN)
		sign = 1;
	if (identifier == 'i' || identifier == 'd')
		return (sign + ft_putnbr_ft_printf(argument, fd));
	else
		return (ft_putchar_fd((char)argument, 1), 1);
	return (0);
}

int	print_arg(int fd, va_list argptr, char identifier)
{
	char	*str;

	if (identifier == 's')
	{
		str = va_arg(argptr, char *);
		if (!str)
			return (ft_putstr_ft_printf("(null)", fd));
		return (ft_putstr_ft_printf(str, fd));
	}
	else if (ft_strchr("cid", identifier) != 0)
		return (print_int_char(fd, va_arg(argptr, int), identifier));
	else if (identifier == '%')
		return (write(1, "%", 1));
	else if (identifier == 'u')
		return (ft_putnbr_ft_printf(va_arg(argptr, unsigned int), fd));
	else if (identifier == 'p')
		return (print_ptr(fd, va_arg(argptr, intptr_t)));
	else if (identifier == 'x' || identifier == 'X')
		return (print_hex(fd, va_arg(argptr, unsigned int), identifier));
	else
		return (write(1, &identifier, 1));
}
