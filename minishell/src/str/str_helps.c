/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_helps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:15:00 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/18 16:06:05 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	ft_strcat_start(char *str, char *start)
{
	int	i;
	int	len;
	int	start_len;

	if (str == NULL || start == NULL)
		return ;
	start_len = ft_strlen(start);
	len = ft_strlen(str);
	i = -1;
	while (++i < len)
		str[start_len + len - 1 - i] = str[len - 1 - i];
	str[start_len + len] = '\0';
	ft_memcpy(str, start, start_len);
}

void	ft_strcat(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	while (*src != '\0')
		dest[i++] = *(src++);
	dest[i] = '\0';
}

int	ft_strstart(char *big, char *little)
{
	int	big_len;
	int	little_len;

	if (big == NULL || little == NULL)
		return (0);
	little_len = ft_strlen(little);
	big_len = ft_strlen(big);
	if (little_len > big_len)
		return (0);
	while (*little != '\0')
		if (*(little++) != *(big++))
			return (0);
	return (1);
}

char	*sub_str(char *str, int start, int end)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (end - start + 1));
	if (res == NULL)
		return (NULL);
	res[end - start] = '\0';
	i = start - 1;
	while (++i < end)
		res[i - start] = str[i];
	return (res);
}
