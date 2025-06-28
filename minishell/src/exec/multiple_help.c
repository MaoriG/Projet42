/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:55:38 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/19 17:15:54 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_processes(t_msh_process *processes,
		t_msh_cmd *cmd, int cmd_len, t_msh_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < cmd_len)
	{
		processes[i].cmd = cmd;
		processes[i].ctx = ctx;
		pipe(processes[i].pipes);
		if (cmd[i].here_doc != NULL && cmd[i].type_in == 2)
		{
			pipe(processes[i].heredoc_pipes);
			write(processes[i].heredoc_pipes[1], cmd[i].here_doc,
				ft_strlen(cmd[i].here_doc));
		}
	}
}

void	msh_close_heredocs(t_msh_process *processes, int cmd_len)
{
	int	i;

	i = -1;
	while (++i < cmd_len)
	{
		if (processes[i].cmd[i].here_doc != NULL
			&& processes[i].cmd[i].type_in == 2)
		{
			close(processes[i].heredoc_pipes[0]);
			close(processes[i].heredoc_pipes[1]);
		}
	}
}

void	close_pipes(t_msh_process *processes, int cmd_len)
{
	int	i;

	i = -1;
	while (++i < cmd_len)
	{
		close(processes[i].pipes[0]);
		close(processes[i].pipes[1]);
	}
	msh_close_heredocs(processes, cmd_len);
}
