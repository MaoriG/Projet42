/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:45:22 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/19 19:18:13 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	word = malloc(sizeof(char) + (len + 1));
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
				free_tab(tab);
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
	tab = malloc(sizeof(char *) + (words + 1));
	if (!tab)
		return (NULL);
	if (!set_mem(tab, s, c))
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

char	*join_path(char *dir, char *cmd)
{
	size_t	len_dir;
	size_t	len_cmd;
	size_t	total_len;
	char	*full_path;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	total_len = len_dir + 1 + len_cmd + 1;
	full_path = malloc(total_len + 1);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	full_path[len_dir] = '/';
	ft_strcpy(full_path + len_dir + 1, cmd);
	return (full_path);
}
