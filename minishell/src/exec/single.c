/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:28:06 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 19:06:30 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	init_heredoc_pipe(int pipes[2], t_msh_cmd *cmd)
{
	if (cmd->here_doc != NULL && cmd->type_in == 2)
		pipe(pipes);
}

static void	read_close_heredoc(int pipes[2], t_msh_cmd *cmd, int do_dup)
{
	if (cmd->here_doc != NULL && cmd->type_in == 2)
	{
		if (do_dup)
			dup2(pipes[0], STDIN_FILENO);
		else
			write(pipes[1], cmd->here_doc, ft_strlen(cmd->here_doc));
		close(pipes[0]);
		close(pipes[1]);
	}
}

static int	do_redir(t_msh_cmd *cmd)
{
	if (cmd->redir_out != NULL && cmd->type_out == 1)
		if (msh_redir_out(cmd))
			return (1);
	if (cmd->redir_in != NULL && cmd->type_in == 1)
		if (msh_redir_in(cmd))
			return (1);
	if (cmd->append_out != NULL && cmd->type_out == 2)
		if (msh_redir_append(cmd))
			return (1);
	return (0);
}

static void	msh_free_helper(t_msh_ctx *ctx, t_msh_cmd *cmd, int err_code)
{
	if (err_code == 127)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd->name, ft_strlen(cmd->name));
		write(STDERR_FILENO, ": command not found\n", 20);
	}
	msh_free_ctx(ctx);
	msh_free_cmds(cmd, 1);
	rl_clear_history();
	exit(err_code);
}

void	msh_exec_cmd_single(t_msh_ctx *ctx, t_msh_cmd *cmd)
{
	int	pipes[2];
	int	pid;

	cmd->path = msh_find_cmd(cmd->name, &cmd->is_builtin, ctx);
	if (cmd->is_builtin)
		return (exec_builtin(ctx, cmd));
	init_heredoc_pipe(pipes, cmd);
	pid = fork();
	is_executing(1, 1);
	if (pid == 0)
	{
		if (cmd->path == NULL)
			msh_free_helper(ctx, cmd, 127);
		read_close_heredoc(pipes, cmd, 1);
		if (do_redir(cmd))
			msh_free_helper(ctx, cmd, 1);
		if (msh_launch_file(ctx, cmd))
			msh_free_helper(ctx, cmd, 127);
		else
			msh_free_helper(ctx, cmd, 1);
	}
	read_close_heredoc(pipes, cmd, 0);
	waitpid(pid, &ctx->last_status, 0);
	msh_set_env(ctx, "_", cmd->argv[cmd->argc - 1]);
	is_executing(1, 0);
}
