/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:14:51 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/07 19:10:59 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - ('A' - 'a'));
	return (c);
}
/*
int	main(void)
{
	char lower = 't';
	char upper = ft_tolower(lower); // Convertir en majuscule

	printf("Caractère original : '%c'\n", lower);
	printf("Caractère en majuscule : '%c'\n", upper);

	// Tester un caractère déjà en majuscule
	lower = 'G';
	upper = ft_tolower(lower);
	printf("Caractère original : '%c'\n", lower);
	printf("Caractère en majuscule : '%c'\n", upper);

	// Tester un caractère non alphabétique
	lower = '1';
	upper = ft_tolower(lower);
	printf("Caractère original : '%c'\n", lower);
	printf("Caractère en majuscule : '%c'\n", upper);

	return (0);
} */