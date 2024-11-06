/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:43:43 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/06 12:55:32 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	int				in;

	i = 0;
	in = 0;
	while (s1[in] == s2[in] && s1[in] != '\0' && s2[in] != '\0' && i < n)
	{
		i++;
		in++;
	}
	if (i == n)
		return (0);
	return (s1[in] - s2[in]);
}
/*#include <stdio.h>

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
}*/