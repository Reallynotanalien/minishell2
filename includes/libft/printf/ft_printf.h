/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:46:56 by edufour           #+#    #+#             */
/*   Updated: 2023/12/18 18:25:03 by edufour          ###   ########.fr       */
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
int		print_ptr(int fd, uintptr_t ptr);

//Utils
int		ft_putstr_ft_printf(char *s, int fd);
int		ft_putnbr_ft_printf(long long n, int fd);

#endif
