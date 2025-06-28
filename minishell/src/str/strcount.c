/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcount.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:24:06 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/17 21:26:41 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcount(const char *str, char c)
{
	int	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
