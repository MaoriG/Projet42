/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:20:26 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/07 19:07:29 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;
	size_t				i;

	d = (unsigned char *)dest;
	if (dest == src || n == 0)
		return (dest);
	if (d > s)
		while (n--)
			d[n] = s[n];
	else
		i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/* int	main(void)
{
	char buffer[20] = "Hello, World";
	printf("avant ft_memmove: %s\n", buffer);
	ft_memmove(buffer + 7, buffer, 5);
	buffer[12] = '\0';
	unsigned long j = 0;
	printf("Apres ft_memmove: %s\n", buffer);
	return (0);
}  */