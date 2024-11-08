/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:43:43 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/07 19:10:06 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		i++;
	}
	if (i == n || (s1[i] == s2[i]))
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/* 
int	main(void)
{
	char s1[] = "jjjjj";
	char s2[] = "jjjjj";
	int result;

	result = ft_strncmp(s1, s2, 11);
	if (result == 0)
	{
		printf("Les chaînes sont égales\n");
	}
	else if (result < 0)
	{
		printf("str1 est inférieur à str2\n");
	}
	else
	{
		printf("str1 est supérieur à str2\n");
	}
	return (0);
} */