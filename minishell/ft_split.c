/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:57:54 by mgobert           #+#    #+#             */
/*   Updated: 2025/04/07 21:26:28 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(tab);
	tab = NULL;
	return ;
}

static char	*allocate_word(char const *s, char c)
{
	size_t	len;
	size_t	i;
	size_t	y;
	char	*word;

	len = 0;
	i = 0;
	y = 0;
	while (s[len] && s[len] != c && s[len] != '\n')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	if (s[i] == ' ')
		i++;
	while (i < len)
	{
		word[y] = s[i];
		i++;
		y++;
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
		if (s[i] != c && s[i] != '\n')
		{
			words++;
			while (s[i] && s[i] != c && s[i] != '\n')
				i++;
		}
		else
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
		if (s[i] != c && s[i] != '\n')
		{
			tab[i_tab] = allocate_word(s + i, c);
			if (!tab[i_tab])
			{
				free_tab(tab, i_tab);
				return (0);
			}
			i_tab++;
			while (s[i] && s[i] != c && s[i] != '\n')
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
		free(tab);
		return (NULL);
	}
	return (tab);
}