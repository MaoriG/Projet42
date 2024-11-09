/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:15:10 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/09 17:11:17 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		is_neg;
	long	num;

	num = n;
	is_neg = (num < 0);
	i = count_digits(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (is_neg)
		num = -num;
	result = malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[i--] = '\0';
	while (num > 0)
	{
		result[i--] = (num % 10) + '0';
		num = num / 10;
	}
	if (is_neg)
		result[0] = '-';
	return (result);
}
/*
int	main(void)
{
	int numbers[] = {0, 123, -456, 7890, -2147483648, 2147483647};
	int num_tests = sizeof(numbers) / sizeof(numbers[0]);
	char *result;

	for (int i = 0; i < num_tests; i++)
	{
		result = ft_itoa(numbers[i]);
		if (result)
		{
			printf("ft_itoa(%d) = \"%s\"\n", numbers[i], result);
			free(result); // Libération de la mémoire allouée par ft_itoa
		}
		else
		{
			printf("ft_itoa(%d) a échoué (retourné NULL)\n", numbers[i]);
		}
	}

	return (0);
} */