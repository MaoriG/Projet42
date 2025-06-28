/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:38:24 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 18:24:18 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static void	ft_str_rm_start(char *str, int start_len)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = start_len - 1;
	while (++i < len)
		str[i - start_len] = str[i];
	str[i - start_len] = '\0';
}

static void	msh_reduce_path(char *path, t_msh_ctx *ctx)
{
	char	*home;
	int		home_len;

	home = msh_get_env(ctx, "HOME", NULL);
	if (home == NULL || !ftstrcmp(home, ""))
		return ;
	if (!ft_strstart(path, home))
		return ;
	home_len = ft_strlen(home);
	ft_str_rm_start(path, home_len);
	ft_strcat_start(path, "~");
}

static char	*get_prompt_userless(char *path)
{
	char	*res;

	res = ft_calloc(sizeof(char), (ft_strlen(path) + 19 + 1));
	if (res == NULL)
		return (NULL);
	ft_strcat(res, "\001\033[01;34m\002");
	ft_strcat(res, path);
	ft_strcat(res, "\001\033[00m\002");
	ft_strcat(res, "$ ");
	return (res);
}

char	*msh_get_prompt(t_msh_ctx *ctx)
{
	char	*path;
	char	*user;
	char	*res;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (NULL);
	msh_reduce_path(path, ctx);
	user = msh_get_env(ctx, "USER", NULL);
	if (user == NULL)
		return (get_prompt_userless(path));
	res = ft_calloc(sizeof(char), (ft_strlen(path) + ft_strlen(user) + 30 + 1));
	if (res == NULL)
		return (free(path), NULL);
	ft_strcat(res, "\001\033[01;32m\002");
	ft_strcat(res, user);
	ft_strcat(res, ":");
	ft_strcat(res, "\001\033[01;34m\002");
	ft_strcat(res, path);
	ft_strcat(res, "\001\033[00m\002");
	ft_strcat(res, "$ ");
	free(path);
	return (res);
}
