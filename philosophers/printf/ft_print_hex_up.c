/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_up.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:01:23 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/15 13:51:23 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_hex_up_digit(char hex_digits[16])
{
	hex_digits[0] = '0';
	hex_digits[1] = '1';
	hex_digits[2] = '2';
	hex_digits[3] = '3';
	hex_digits[4] = '4';
	hex_digits[5] = '5';
	hex_digits[6] = '6';
	hex_digits[7] = '7';
	hex_digits[8] = '8';
	hex_digits[9] = '9';
	hex_digits[10] = 'A';
	hex_digits[11] = 'B';
	hex_digits[12] = 'C';
	hex_digits[13] = 'D';
	hex_digits[14] = 'E';
	hex_digits[15] = 'F';
}

int	print_hex_up(unsigned int nb)
{
	int		count;
	char	hex_digits[16];
	char	buffer[32];
	int		i;

	count = 0;
	i = 0;
	init_hex_up_digit(hex_digits);
	if (nb == 0)
		buffer[i++] = '0';
	while (nb > 0)
	{
		buffer[i++] = hex_digits[nb % 16];
		nb /= 16;
	}
	while (i > 0)
		count += print_c(buffer[--i]);
	return (count);
}
