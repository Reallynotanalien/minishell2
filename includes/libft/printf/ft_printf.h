/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:36:30 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:36:32 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define HEX_MIN "0123456789abcdef"
# define HEX_MAJ "0123456789ABCDEF"

# include "../libft.h"
# include <stdarg.h>
# include <limits.h>

void	ft_printf(int fd, const char *format, ...);
int		print_arg(int fd, va_list argptr, char identifier);
int		print_hex(int fd, unsigned int argument, char identifier);
int		print_ptr(int fd, intptr_t ptr);

//Utils
int		ft_putstr_ft_printf(char *s, int fd);
int		ft_putnbr_ft_printf(long long n, int fd);

#endif
