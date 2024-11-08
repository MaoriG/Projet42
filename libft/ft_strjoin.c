/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:04:12 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/08 13:36:47 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ftstrlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s3 = malloc(((ftstrlen(s1) + ftstrlen(s2)) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

/* int	main(void)
{
	// Chaînes à joindre
	const char *str1 = "Bonjour, ";
	const char *str2 = "le monde !";

	// Appelle ft_strjoin pour joindre les chaînes
	char *result = ft_strjoin(str1, str2);

	// Vérifie si l'allocation et la concaténation ont réussi
	if (result != NULL)
	{
		// Affiche la chaîne résultante
		printf("Chaîne résultante : %s\n", result);
		// Libère la mémoire allouée
		free(result);
	}
	else
	{
		printf("Erreur : échec de la concaténation.\n");
	}

	return (0);
}  */