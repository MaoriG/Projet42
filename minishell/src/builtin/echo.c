/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:27:04 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/18 15:29:38 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	is_dash_n(char *str)
{
	if (str[0] != '-')
		return (0);
	str++;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

int	msh_blt_echo(int argc, char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (i < argc && is_dash_n(argv[i]))
	{
		i++;
		newline = 0;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i + 1 < argc)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
