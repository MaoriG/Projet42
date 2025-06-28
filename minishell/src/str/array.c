/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:23:33 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/18 15:58:39 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_memcpy(void *dest, const void *src, int len)
{
	while (len-- > 0)
		((char *)dest)[len] = ((char *)src)[len];
}
