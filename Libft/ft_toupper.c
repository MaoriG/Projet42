/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:07:30 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/05 16:38:24 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}
/*#include <stdio.h> // Pour printf

 int main()
{
	char lower = 't';
	char upper = ft_toupper(lower); // Convertir en majuscule

	printf("Caractère original : '%c'\n", lower);
	printf("Caractère en majuscule : '%c'\n", upper);

	// Tester un caractère déjà en majuscule
	lower = 'G';
	upper = ft_toupper(lower);
	printf("Caractère original : '%c'\n", lower);
	printf("Caractère en majuscule : '%c'\n", upper);

	// Tester un caractère non alphabétique
	lower = '1';
	upper = ft_toupper(lower);
	printf("Caractère original : '%c'\n", lower);
	printf("Caractère en majuscule : '%c'\n", upper);

	return (0);
} */