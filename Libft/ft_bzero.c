/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:20:45 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/05 12:23:00 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void ft_bzero (void *ptr, unsigned int n)
{
    unsigned char *p = (unsigned char *)ptr;
    unsigned int i = 0;
    while (i < n)
    {
        p[i] = 0;
        i++; 
    }
}