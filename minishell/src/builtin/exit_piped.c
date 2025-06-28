/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_piped.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:21:40 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/18 15:32:46 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	clean_all(t_msh_process *processes,
		int cmd_len, t_msh_ctx *ctx, int i)
{
	msh_free_ctx(ctx);
	msh_free_cmds(processes[i].cmd, cmd_len);
	free(processes);
	rl_clear_history();
}

static void	no_arg(t_msh_process *processes, int cmd_len, t_msh_ctx *ctx, int i)
{
	write(STDERR_FILENO, "exit\n", 5);
	clean_all(processes, cmd_len, ctx, i);
	exit(0);
}

static void	one_arg(t_msh_process *processes,
		int cmd_len, t_msh_ctx *ctx, int i)
{
	int		is_int;
	int64_t	exit_code;

	is_int = !ft_atoi(processes[i].cmd[i].argv[1], &exit_code);
	if (!is_int)
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, processes[i].cmd[i].argv[1],
			ft_strlen(processes[i].cmd[i].argv[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit_code = 2;
	}
	if (is_int)
		write(STDERR_FILENO, "exit\n", 5);
	clean_all(processes, cmd_len, ctx, i);
	exit(exit_code % 256);
}

void	msh_blt_exit2(t_msh_process *processes, int cmd_len,
		t_msh_ctx *ctx, int i)
{
	if (processes[i].cmd[i].argc == 1)
		no_arg(processes, cmd_len, ctx, i);
	if (processes[i].cmd[i].argc == 2)
		one_arg(processes, cmd_len, ctx, i);
	write(STDERR_FILENO, "exit\nminishell: exit: too many arguments\n", 41);
	clean_all(processes, cmd_len, ctx, i);
	exit(1);
}
