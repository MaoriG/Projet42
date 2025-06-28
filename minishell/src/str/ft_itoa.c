/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:05:23 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/07 18:50:11 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	number_len(int n)
{
	int	count;

	if (n < 0)
		return (number_len(-n) + 1);
	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = number_len(n);
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	while (n > 0 && len - 1 >= 0)
	{
		res[len - 1] = '0' + (n % 10);
		n /= 10;
		len--;
	}
	return (res);
}
