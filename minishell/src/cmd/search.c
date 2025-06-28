/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:22:18 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 18:23:36 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	*get_path(t_msh_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->env_len)
		if (!ftstrcmp(ctx->env[i].name, "PATH"))
			return (ctx->env[i].value);
	return (NULL);
}

static int	is_file(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (0);
	if (S_ISDIR(buf.st_mode))
		return (0);
	if (S_ISREG(buf.st_mode))
		return (1);
	return (0);
}

char	*path_contains(char *path, char *name, int *p_len)
{
	int		n_len;
	char	*cmd_path;

	*p_len = 0;
	while (path[*p_len] != '\0' && path[*p_len] != ':')
		(*p_len)++;
	n_len = ft_strlen(name);
	cmd_path = malloc(sizeof(char) * (*p_len + 1 + n_len + 1));
	if (cmd_path == NULL)
		return (NULL);
	cmd_path[*p_len] = '/';
	ft_memcpy(cmd_path, path, *p_len);
	ft_memcpy(&cmd_path[*p_len + 1], name, n_len + 1);
	if (access(cmd_path, F_OK | X_OK) == 0 && is_file(cmd_path))
		return (cmd_path);
	return (free(cmd_path), NULL);
}

int	check_is_builtin(char *name, uint8_t *is_builtin)
{
	*is_builtin = 1;
	if (!ftstrcmp(name, "cd"))
		return (1);
	if (!ftstrcmp(name, "pwd"))
		return (1);
	if (!ftstrcmp(name, "echo"))
		return (1);
	if (!ftstrcmp(name, "exit"))
		return (1);
	if (!ftstrcmp(name, "env"))
		return (1);
	if (!ftstrcmp(name, "export"))
		return (1);
	if (!ftstrcmp(name, "unset"))
		return (1);
	*is_builtin = 0;
	return (0);
}

char	*msh_find_cmd(char *name, uint8_t *is_builtin, t_msh_ctx *ctx)
{
	int		i;
	char	*path;
	int		path_len;
	char	*res;

	*is_builtin = 0;
	if (ft_strchr(name, '/') != -1)
	{
		if (access(name, F_OK | X_OK) == 0 && is_file(name))
			return (ft_strdup(name));
		return (NULL);
	}
	if (check_is_builtin(name, is_builtin))
		return (NULL);
	i = 0;
	path = get_path(ctx);
	res = NULL;
	while (path != NULL && path[i] != '\0' && res == NULL)
	{
		res = path_contains(&path[i], name, &path_len);
		i += path_len;
		if (path[i] == ':')
			i++;
	}
	return (res);
}
