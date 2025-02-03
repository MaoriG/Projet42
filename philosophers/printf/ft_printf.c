/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:24:36 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/18 14:04:24 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	print_format(va_list args, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += print_c(va_arg(args, int));
	else if (format == 's')
		count += print_str(va_arg(args, char *));
	else if (format == 'p')
		count += print_ptr(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		count += print_nb(va_arg(args, int));
	else if (format == 'u')
		count += print_u(va_arg(args, unsigned int));
	else if (format == 'x')
		count += print_hex(va_arg(args, unsigned int));
	else if (format == 'X')
		count += print_hex_up(va_arg(args, unsigned int));
	else if (format == '%')
		count += print_c('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	va_start(ap, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += print_format(ap, format[i]);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
