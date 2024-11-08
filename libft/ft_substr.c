/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:56 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/07 19:10:51 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	i_len;
	char	*copie;

	i_len = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i_len] != '\0')
		i_len++;
	if (start >= i_len)
		return (ft_calloc(1, 1));
	if (len > i_len - start)
		len = i_len - start;
	copie = malloc((len + 1) * (sizeof(char)));
	if (copie == NULL)
		return (NULL);
	while (i < len)
	{
		copie[i] = s[start + i];
		i++;
	}
	copie[i] = '\0';
	return (copie);
}
/*
int	main(void)
{
	char *str = "Hello, World!";
	char *copie;

	// Exemple 1 : Extraire "World" en commençant à l'indice 7
	copie = ft_substr(str, 4, 5);
	printf("Sous-chaîne extraite (\"World\") : %s\n", copie);
	free(copie); // Libérer la mémoire après utilisation

	// Exemple 2 : Extraire "Hello" en commençant à l'indice 0
	copie = ft_substr(str, 0, 5);
	printf("Sous-chaîne extraite (\"Hello\") : %s\n", copie);
	free(copie);

	// Exemple 3 : Demander une sous-chaîne plus longue que le reste de la chaîne
	copie = ft_substr(str, 7, 20);
	printf("Sous-chaîne extraite (\"World!\") : %s\n", copie);
	free(copie);

	// Exemple 4 : Demander une sous-chaîne en dehors de la longueur de la chaîne
	copie = ft_substr(str, 20, 5);
	printf("Sous-chaîne extraite (chaîne vide attendue) : %s\n", copie);
	free(copie);

	return (0);
} */
