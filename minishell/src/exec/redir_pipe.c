/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:53:13 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/19 18:07:14 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msh_redir_first(t_msh_process *processes, int cmd_len, int i)
{
	if (processes[i].cmd[i].redir_in != NULL
		&& processes[i].cmd[i].type_in == 1)
		if (msh_redir_in(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].here_doc != NULL
		&& processes[i].cmd[i].type_in == 2)
		dup2(processes[i].heredoc_pipes[0], STDIN_FILENO);
	if (processes[i].cmd[i].redir_out != NULL
		&& processes[i].cmd[i].type_out == 1)
		if (msh_redir_out(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].append_out != NULL
		&& processes[i].cmd[i].type_out == 2)
		if (msh_redir_append(processes[i].cmd + i))
			return (1);
	if (!processes[i].cmd[i].redir_out && !processes[i].cmd[i].append_out)
		dup2(processes[i].pipes[1], STDOUT_FILENO);
	close_pipes(processes, cmd_len);
	return (0);
}

static int	msh_redir_last(t_msh_process *processes, int cmd_len, int i)
{
	if (processes[i].cmd[i].redir_in != NULL
		&& processes[i].cmd[i].type_in == 1)
		if (msh_redir_in(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].here_doc != NULL
		&& processes[i].cmd[i].type_in == 2)
		dup2(processes[i].heredoc_pipes[0], STDIN_FILENO);
	if (processes[i].cmd[i].redir_out != NULL
		&& processes[i].cmd[i].type_out == 1)
		if (msh_redir_out(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].append_out != NULL
		&& processes[i].cmd[i].type_out == 2)
		if (msh_redir_append(processes[i].cmd + i))
			return (1);
	if (!processes[i].cmd[i].redir_in && !processes[i].cmd[i].here_doc)
		dup2(processes[i - 1].pipes[0], STDIN_FILENO);
	close_pipes(processes, cmd_len);
	return (0);
}

static int	msh_redir_middle(t_msh_process *processes, int cmd_len, int i)
{
	if (processes[i].cmd[i].redir_in != NULL
		&& processes[i].cmd[i].type_in == 1)
		if (msh_redir_in(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].here_doc != NULL
		&& processes[i].cmd[i].type_in == 2)
	{
		dup2(processes[i].heredoc_pipes[0], STDIN_FILENO);
		return (0);
	}
	if (processes[i].cmd[i].redir_out != NULL
		&& processes[i].cmd[i].type_out == 1)
		if (msh_redir_out(processes[i].cmd + i))
			return (1);
	if (processes[i].cmd[i].append_out != NULL
		&& processes[i].cmd[i].type_out == 2)
		if (msh_redir_append(processes[i].cmd + i))
			return (1);
	if (!processes[i].cmd[i].redir_in && !processes[i].cmd[i].here_doc)
		dup2(processes[i - 1].pipes[0], STDIN_FILENO);
	if (!processes[i].cmd[i].redir_out && !processes[i].cmd[i].append_out)
		dup2(processes[i].pipes[1], STDOUT_FILENO);
	close_pipes(processes, cmd_len);
	return (0);
}

// process[N] write to pipe[N]
// process[N] read to pipe[N - 1]
int	msh_do_redir_pipe(t_msh_process *processes, int cmd_len, int i)
{
	if (i == 0)
		return (msh_redir_first(processes, cmd_len, i));
	if (i == cmd_len - 1)
		return (msh_redir_last(processes, cmd_len, i));
	return (msh_redir_middle(processes, cmd_len, i));
}
