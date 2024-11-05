/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:20:26 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/05 14:42:11 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
void	ft_memmove (void *dest, const void *src, size_t n)
{
	unsigned char *d = (unsigned char *) dest;
	unsigned char *s = (unsigned char *) src;
	
	if (d < s)
	{
		size_t i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else 
	{
		size_t i = n; 
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
}
/* int main (void)
{
	char buffer[20] = "Hello, World";
	printf ("avant ft_memmove: %s\n", buffer);
	ft_memmove (buffer + 7, buffer, 5);
	buffer [12] = '\0';
	unsigned long j = 0;
	printf("Apres ft_memmove: %s\n", buffer);
	return 0;
} */