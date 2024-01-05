/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:36:45 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/04 19:36:47 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ui_to_hex(int fd, unsigned int nb, char *base, int *nb_char)
{
	if (nb / 16 > 0)
		ui_to_hex(fd, nb / 16, base, nb_char);
	*nb_char += write(1, base + (nb % 16), 1);
}

int	print_hex(int fd, unsigned int nb, char identifier)
{
	int		nb_char;

	nb_char = 0;
	if (identifier == 'x')
		ui_to_hex(fd, nb, HEX_MIN, &nb_char);
	else
		ui_to_hex(fd, nb, HEX_MAJ, &nb_char);
	return (nb_char);
}
