/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:14:51 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/05 16:28:47 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - ('A' - 'a'));
	return (c);
}
/* #include <stdio.h> // Pour printf

int	main(void)
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