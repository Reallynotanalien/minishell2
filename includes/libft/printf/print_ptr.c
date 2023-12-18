/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:44:41 by edufour           #+#    #+#             */
/*   Updated: 2023/12/18 17:27:41 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ptr_to_hex(int fd, uintptr_t ptr, char *base, int *nb_char)
{
	if (ptr / ft_strlen(base))
		ptr_to_hex(fd, ptr / ft_strlen(base), base, nb_char);
	*nb_char += write(1, base + (ptr % ft_strlen(base)), 1);
}

int	print_ptr(int fd, uintptr_t ptr)
{
	int		nb_char;

	if (!ptr)
		return (write(1, "0x0", 3));
	nb_char = write(1, "0x", 2);
	ptr_to_hex(fd, ptr, HEX_MIN, &nb_char);
	return (nb_char);
}
