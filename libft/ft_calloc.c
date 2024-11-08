/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:16:54 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/07 19:08:04 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void			*ptr;
	unsigned char	*p;
	size_t			i;

	ptr = malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < num * size)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
/*
int	main(void)
{
	int *arr;
	size_t num_elements = 5;

	// Allouer de la mémoire pour 5 entiers et les initialiser à zéro
	arr = (int *)ft_calloc(num_elements, sizeof(int));

	// Vérifier si l'allocation a réussi
	if (arr == NULL)
	{
		printf("Erreur d'allocation mémoire\n");
		return (1);
	}

	// Afficher les valeurs dans le tableau
	for (size_t i = 0; i < num_elements; i++)
	{
		printf("arr[%zu] = %d\n", i, arr[i]);
	}

	// Libérer la mémoire allouée
	free(arr);

	return (0);
} */