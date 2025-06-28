/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:12:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 18:23:45 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_redir_blt(t_msh_cmd *cmd)
{
	if (msh_redir_out(cmd))
		return (1);
	if (msh_redir_append(cmd))
		return (1);
	if (msh_redir_in(cmd))
		return (1);
	return (0);
}

void	exec_builtin(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	int	old_fd;

	old_fd = dup(STDOUT_FILENO);
	if (msh_redir_blt(cmd))
		ctx->last_status = 1;
	else if (ftstrcmp(cmd->name, "cd") == 0)
		ctx->last_status = msh_blt_cd(cmd->argc, cmd->argv, ctx);
	else if (ftstrcmp(cmd->name, "pwd") == 0)
		ctx->last_status = msh_blt_pwd(cmd->argc, cmd->argv, ctx);
	else if (ftstrcmp(cmd->name, "echo") == 0)
		ctx->last_status = msh_blt_echo(cmd->argc, cmd->argv);
	else if (ftstrcmp(cmd->name, "export") == 0)
		ctx->last_status = builtin_export(cmd->argc, cmd->argv, ctx);
	else if (ftstrcmp(cmd->name, "unset") == 0)
		ctx->last_status = builtin_unset(cmd->argc, cmd->argv, ctx);
	else if (ftstrcmp(cmd->name, "env") == 0)
		ctx->last_status = builtin_env(ctx);
	else if (ftstrcmp(cmd->name, "exit") == 0)
		ctx->last_status = msh_blt_exit(cmd, ctx, old_fd);
	dup2(old_fd, STDOUT_FILENO);
	close(old_fd);
}
