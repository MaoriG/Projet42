/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:44:53 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/07 16:19:02 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;
	size_t	i;

	len = 0;
	while (s[len] != '\0')
		len++;
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
/* #include <stdio.h>
int	main(void)
{
	const char *str = "Hello, World!";

	// Appel à ft_strdup pour dupliquer la chaîne
	char *duplicate = ft_strdup(str);

	// Vérification si la duplication a réussi
	if (duplicate != NULL)
	{
		printf("Chaîne d'origine : %s\n", str);
		printf("Chaîne dupliquée : %s\n", duplicate);

		// Libérer la mémoire allouée pour la copie
		free(duplicate);
	}
	else
	{
		printf("Échec de la duplication de la chaîne.\n");
	}

	return (0);
} */