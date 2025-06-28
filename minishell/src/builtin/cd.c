/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:41:23 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/20 18:22:58 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"

static int	cd_to_home(t_msh_ctx *ctx)
{
	char	*home;

	home = msh_get_env(ctx, "HOME", NULL);
	if (!home)
	{
		write(STDERR_FILENO, "minishell: cd: HOME not set\n", 29);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static int	cd_to_previous(t_msh_ctx *ctx)
{
	char	*old_pwd;

	old_pwd = msh_get_env(ctx, "OLDPWD", NULL);
	if (!old_pwd)
	{
		write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 30);
		return (1);
	}
	if (chdir(old_pwd) == -1)
	{
		perror("cd");
		return (1);
	}
	printf("%s\n", old_pwd);
	return (0);
}

static int	cd_to_directory(char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static void	update_pwd_env(t_msh_ctx *ctx)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		perror("cd");
		return ;
	}
	msh_set_env(ctx, "OLDPWD", msh_get_env(ctx, "PWD", NULL));
	msh_set_env(ctx, "PWD", current_dir);
	free(current_dir);
}

int	msh_blt_cd(int argc, char **argv, t_msh_ctx *ctx)
{
	int	ret;

	if (argc > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	ret = 0;
	if (argc == 1)
		ret = cd_to_home(ctx);
	else if (ftstrcmp(argv[1], "-") == 0)
		ret = cd_to_previous(ctx);
	else
		ret = cd_to_directory(argv[1]);
	if (ret == 0)
		update_pwd_env(ctx);
	return (ret);
}
