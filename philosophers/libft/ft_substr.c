/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:56 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/12 11:07:10 by mgobert          ###   ########.fr       */
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
