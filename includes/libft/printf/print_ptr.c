/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:36:51 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:36:53 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ptr_to_hex(int fd, intptr_t ptr, char *base, int *nb_char)
{
	if (ptr / ft_strlen(base))
		ptr_to_hex(fd, ptr / ft_strlen(base), base, nb_char);
	*nb_char += write(1, base + (ptr % ft_strlen(base)), 1);
}

int	print_ptr(int fd, intptr_t ptr)
{
	int		nb_char;

	if (!ptr)
		return (write(1, "0x0", 3));
	nb_char = write(1, "0x", 2);
	ptr_to_hex(fd, ptr, HEX_MIN, &nb_char);
	return (nb_char);
}
