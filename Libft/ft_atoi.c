/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:14:51 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/06 15:01:42 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
/* #include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	const char *str1 = "  +42";   // Chaîne avec un nombre négatif
	const char *str2 = "hkjk12345"; // Chaîne avec un nombre positif
	const char *str3 = "-42abc";
		// Chaîne avec un nombre suivi de caractères non numériques
	const char *str4 = "   +0";   // Chaîne avec un nombre positif égal à 0

	printf("Conversion de \"%s\" : %d\n", str1, ft_atoi(str1));
	printf("Conversion de \"%s\" : %d\n", str2, ft_atoi(str2));
	printf("Conversion de \"%s\" : %d\n", str3, ft_atoi(str3));
	printf("Conversion de \"%s\" : %d\n", str4, ft_atoi(str4));

	printf("Conversion de \"%s\" : %d\n", str1, atoi(str1));
	printf("Conversion de \"%s\" : %d\n", str2, atoi(str2));
	printf("Conversion de \"%s\" : %d\n", str3, atoi(str3));
	printf("Conversion de \"%s\" : %d\n", str4, atoi(str4));

	return (0);
} */