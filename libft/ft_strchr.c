/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:19:02 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/07 19:02:24 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (c == '\0')
		return ((char *)s);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
/*

int	main(void)
{
	const char *str = "Hello, World!";
	char target = 'o';

	char *result = ft_strchr(str, target);
	if (result != NULL)
	{
		printf("Caractère '%c' trouvé à la position : %ld\n", target, result
			- str);
	}
	else
	{
		printf("Caractère '%c' non trouvé.\n", target);
	}

	return (0);
} */