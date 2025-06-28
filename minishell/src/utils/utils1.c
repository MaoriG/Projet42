/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:49:45 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 20:03:37 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/stat.h>

void	*ft_calloc(size_t size, size_t n)
{
	char	*res;

	res = malloc(size * n);
	ft_memset(res, 0, size * n);
	return (res);
}

void	ft_memset(void *ptr, int c, int len)
{
	char	*p;

	p = (char *)ptr;
	while (--len >= 0)
		p[len] = (unsigned char)c;
}

int	msh_is_executable(char *path)
{
	struct stat	st;

	if (path == NULL)
		return (0);
	if (stat(path, &st) == -1)
		return (0);
	if (S_ISREG(st.st_mode))
		return (1);
	return (0);
}

int	tab_len(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

void	print_banner(void)
{
	printf("  __  __ _____ _   _ _____ _    _  _____ ______ _      _   \n");
	printf(" |  \\/  |_   _| \\ | |_   _| |  | |/ ____|  ____| |    | |\n");
	printf(" | \\  / | | | |  \\| | | | | |__| | (___ | |__  | |    | |\n");
	printf(" | |\\/| | | | | . ` | | | |  __  |\\___ \\|  __| | |    | |\n");
	printf(" | |  | |_| |_| |\\  |_| |_| |  | |____) | |____| |____| |____\n");
	printf(" |_|  |_|_____|_| \\_|_____|_|  |_|_____/|______|______|______|\n");
	printf("                                                               \n");
}
