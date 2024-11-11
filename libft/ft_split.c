/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:57:54 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/11 11:32:47 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tab(char **tab, size_t allocated)
{
	size_t	i;

	i = 0;
	while (i < allocated)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	tab = NULL;
	return ;
}

static char	*allocate_word(char const *s, char c)
{
	size_t	len;
	size_t	i;
	char	*word;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	set_mem(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	i_tab;

	i = 0;
	i_tab = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			tab[i_tab] = allocate_word(s + i, c);
			if (!tab[i_tab])
			{
				free_tab(tab, i_tab);
				return (0);
			}
			i_tab++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	tab[i_tab] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**tab;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	if (!set_mem(tab, s, c))
	{
		free (tab);
		return (NULL);
	}
	return (tab);
}
/*  #include <stdio.h>

int	main(void)
{
	// Test avec des espaces comme délimiteur
	char *str1 = "Hello world this is a test";
	char delimiter1 = ' ';
	char **result1 = ft_split(str1, delimiter1);

	printf("Test 1: Split string '%s' by '%c'\n", str1, delimiter1);
	for (int i = 0; result1[i] != NULL; i++)
	{
		printf("Word %d: %s\n", i + 1, result1[i]);
		free(result1[i]); // Libérer chaque mot
	}
	free(result1); // Libérer le tableau des mots

	// Test avec une virgule comme délimiteur
	char *str2 = "apple,banana,cherry";
	char delimiter2 = ',';
	char **result2 = ft_split(str2, delimiter2);

	printf("\nTest 2: Split string '%s' by '%c'\n", str2, delimiter2);
	for (int i = 0; result2[i] != NULL; i++)
	{
		printf("Word %d: %s\n", i + 1, result2[i]);
		free(result2[i]); // Libérer chaque mot
	}
	free(result2); // Libérer le tableau des mots

	// Test avec un cas où il n'y a pas de délimiteur
	char *str3 = "singleword";
	char delimiter3 = ',';
	char **result3 = ft_split(str3, delimiter3);

	printf("\nTest 3: Split string '%s' by '%c'\n", str3, delimiter3);
	for (int i = 0; result3[i] != NULL; i++)
	{
		printf("Word %d: %s\n", i + 1, result3[i]);
		free(result3[i]); // Libérer chaque mot
	}
	free(result3); // Libérer le tableau des mots

	// Test avec un cas où la chaîne est vide
	char *str4 = "";
	char delimiter4 = ' ';
	char **result4 = ft_split(str4, delimiter4);

	printf("\nTest 4: Split empty string\n");
	if (result4)
	{
		for (int i = 0; result4[i] != NULL; i++)
		{
			printf("Word %d: %s\n", i + 1, result4[i]);
			free(result4[i]); // Libérer chaque mot
		}
		free(result4); // Libérer le tableau des mots
	}
	else
	{
		printf("Result is NULL\n");
	}

	return (0);
}  */