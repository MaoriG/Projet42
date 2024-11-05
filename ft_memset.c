/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:14:36 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/05 11:52:26 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_memset(void *ptr, int value, unsigned int num)
{
	unsigned char	*p;
	unsigned int	i;

	p = (unsigned char *) ptr;
	i = 0;
	while (i < num)
	{
		p[i] = (unsigned char)value;
		i++;
	}
}
