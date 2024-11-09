/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:40:08 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/08 17:50:24 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	rchr(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*str;

	start = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && rchr(s1[start], set))
		start++;
	end = len(s1);
	while (end > start && rchr(s1[end - 1], set))
		end--;
	str = (char *)malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*s;
	char	*set;
	char	*trimmed;

	// Définition de la chaîne à tester et du set de caractères à retirer
	s = "   ---Hello World---   ";
	set = " -";
	// Utilisation de ft_strtrim pour retirer les caractères du set
	trimmed = ft_strtrim(s, set);
	if (trimmed == NULL)
	{
		printf("Erreur d'allocation de mémoire.\n");
		return (1);
	}
	// Affichage du résultat
	printf("Chaîne d'origine : '%s'\n", s);
	printf("Set de caractères à retirer : '%s'\n", set);
	printf("Résultat après ft_strtrim : '%s'\n", trimmed);
	// Libération de la mémoire allouée
	free(trimmed);
	return (0);
} */
