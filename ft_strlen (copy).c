/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:57:52 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/05 11:51:41 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strlen(char *str)
{
	int	i;

	while (str[i] != '\0')
		i++;
	return (i);
}
