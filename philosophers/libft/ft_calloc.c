/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:16:54 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/12 11:09:21 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void			*ptr;
	unsigned char	*p;
	size_t			i;

	ptr = malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < num * size)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
