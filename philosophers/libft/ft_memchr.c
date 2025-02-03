/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:04:41 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/12 11:08:52 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	const unsigned char	*p = (const unsigned char *)ptr;
	unsigned int		i;

	i = 0;
	while (i < num)
	{
		if (p[i] == (unsigned char)value)
			return ((void *)(p + i));
		i++;
	}
	return (NULL);
}
