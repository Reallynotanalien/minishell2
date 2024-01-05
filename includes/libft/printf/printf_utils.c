/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:36:56 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:36:59 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_ft_printf(char *s, int fd)
{
	if (!s)
		return (-1);
	return (write(fd, s, ft_strlen(s)));
}

int	ft_putnbr_ft_printf(long long n, int fd)
{
	int	n_count;

	n_count = 1;
	if (n == -2147483648)
		return (ft_putstr_ft_printf("-2147483648", fd));
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = n * -1;
		}
		if (n >= 10)
			n_count += ft_putnbr_ft_printf(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
	return (n_count);
}
