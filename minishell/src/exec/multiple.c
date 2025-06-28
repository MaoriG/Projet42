/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:23:21 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/21 14:39:14 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_file_piped(t_msh_process *processes, int cmd_len,
		t_msh_ctx *ctx, int i)
{
	char	**env;

	if (msh_is_executable(processes[i].cmd[i].path))
	{
		env = msh_build_env(ctx);
		execve(processes[i].cmd[i].path, processes[i].cmd[i].argv, env);
		free(env);
	}
	print_error_found(processes[i].cmd[i].name);
	msh_free_ctx(ctx);
	msh_free_cmds(processes[i].cmd, cmd_len);
	free(processes);
	rl_clear_history();
	exit(127);
}

static void	clean_all(t_msh_process *processes, int cmd_len,
		t_msh_ctx *ctx, int i)
{
	msh_free_cmds(processes[i].cmd, cmd_len);
	msh_free_ctx(ctx);
	free(processes);
	rl_clear_history();
}

static void	exec_builtin_piped(t_msh_process *processes, int cmd_len,
		t_msh_ctx *ctx, int i)
{
	int	status;

	if (ftstrcmp(processes[i].cmd[i].name, "exit") != 0)
	{
		exec_builtin(ctx, &processes[i].cmd[i]);
		status = ctx->last_status;
		clean_all(processes, cmd_len, ctx, i);
		exit(status);
	}
	msh_blt_exit2(processes, cmd_len, ctx, i);
}

static int	*launch_forks(t_msh_process *processes, int cmd_len, t_msh_ctx *ctx)
{
	int	*pids;
	int	i;

	i = -1;
	pids = malloc(sizeof(int) * cmd_len);
	while (++i < cmd_len)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			free(pids);
			if (msh_do_redir_pipe(processes, cmd_len, i))
			{
				close_pipes(processes, cmd_len);
				clean_all(processes, cmd_len, ctx, i);
				exit(1);
			}
			processes[i].cmd[i].path = msh_find_cmd(processes[i].cmd[i].name,
					&processes[i].cmd[i].is_builtin, ctx);
			if (processes[i].cmd[i].is_builtin)
				exec_builtin_piped(processes, cmd_len, ctx, i);
			exec_file_piped(processes, cmd_len, ctx, i);
		}
	}
	return (pids);
}

void	msh_exec_cmd_pipes(t_msh_ctx *ctx, t_msh_cmd *cmd, int cmd_len)
{
	t_msh_process	*processes;
	int				*pids;
	int				i;

	processes = malloc(sizeof(t_msh_process) * cmd_len);
	if (!processes)
		return ;
	init_processes(processes, cmd, cmd_len, ctx);
	is_executing(1, 1);
	pids = launch_forks(processes, cmd_len, ctx);
	close_pipes(processes, cmd_len);
	waitpid(pids[cmd_len - 1], &ctx->last_status, 0);
	i = -1;
	while (++i < cmd_len - 1)
		waitpid(pids[i], NULL, 0);
	is_executing(1, 0);
	free(pids);
	free(processes);
}
