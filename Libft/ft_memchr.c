/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:04:41 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/06 13:20:28 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

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
/*#include <stdio.h>

int	main(void) {
	const char data[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd',
		'!' };
	char target = 'o';

	// Utiliser ft_memchr pour chercher la première occurrence de 'o'
	char *result = (char *)ft_memchr(data, target, sizeof(data));

	if (result != NULL) {
		printf("Caractère '%c' trouvé à la position : %ld\n", target, result
			- data);
	} else {
		printf("Caractère '%c' non trouvé.\n", target);
	}

	return (0);
}*/