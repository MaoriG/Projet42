/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:49:09 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/07 19:10:24 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, unsigned int len)

{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] != '\0' && (i + j) < len && haystack[i
					+ j] == needle[j])
				j++;
			if (needle[j] == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void) {
	const char *haystack = "Hello, World!";
	const char *needle = "World";
	unsigned int len = 16;

	// Utiliser ft_strnstr pour chercher "World" dans "Hello,
		World!" sur les 12 premiers caractères
	char *result = ft_strnstr(haystack, needle, len);

	if (result != NULL) {
		printf("Sous-chaîne trouvée : %s\n", result);
	} else {
		printf("Sous-chaîne non trouvée dans la limite des
			%u premiers caractères.\n", len);
	}

	return (0);
} */