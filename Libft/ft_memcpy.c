/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:34:41 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/05 14:05:41 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void ft_memcpy (void *dest, void *src, unsigned int n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (unsigned char *)src;
    
    int i; 

    i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
}