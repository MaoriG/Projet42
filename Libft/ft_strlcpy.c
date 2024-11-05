/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:46:30 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/05 15:21:42 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
    size_t i = 0;
    while (i < src_len && i < size - 1)
    {
        dest[i] = src[i]; 
        i++;
    }
    dest[i] = '\0';
    return (src_len);
}