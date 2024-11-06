/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:26:12 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/06 13:48:33 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(const void *ptr1, const void *ptr2, unsigned int num)
{
	const unsigned char	*p1 = (const unsigned char *)ptr1;
	const unsigned char	*p2 = (const unsigned char *)ptr2;
	unsigned int		i;

	i = 0;
	while (i < num)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
/* #include <stdio.h>
int	main(void)
{
	const char data1[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l',
		'd', '!' };
	const char data2[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l',
		'd', '!' };
	const char data3[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l',
		'd', '?' };
	unsigned int num = 12;

	// Comparer data1 et data2 (identiques)
	int result1 = ft_memcmp(data1, data2, num);
	if (result1 == 0) {
		printf("data1 et data2 sont identiques sur les %u premiers octets.\n",
			num);
	} else {
		printf("data1 et data2 sont différents : résultat = %d\n", result1);
	}

	// Comparer data1 et data3 (différents au dernier octet)
	int result2 = ft_memcmp(data1, data3, num);
	if (result2 == 0) {
		printf("data1 et data3 sont identiques sur les %u premiers octets.\n",
			num);
	} else {
		printf("data1 et data3 sont différents : résultat = %d\n", result2);
	}

	return (0);
} */