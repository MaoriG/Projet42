/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:32:57 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/15 13:50:02 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int	print_c(char c);
int	ft_printf(const char *format, ...);
int	print_str(char *str);
int	print_nb(int nb);
int	print_hex(unsigned int nb);
int	print_u(unsigned int nb);
int	print_ptr(void *ptr);
int	print_hex_up(unsigned int nb);

#endif 