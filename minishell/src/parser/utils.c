/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:15 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/23 17:01:15 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
	{
		perror(RED "malloc" RST);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

int	skip_space(const char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

char	*ft_substr(const char *s, int start, int len)
{
	int		i;
	int		i_len;
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
