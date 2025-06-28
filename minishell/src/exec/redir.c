/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:37:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/18 15:57:55 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

int	msh_redir_in(t_msh_cmd *cmd)
{
	int	tmp;

	if (cmd->redir_in != NULL && cmd->type_in == 1)
	{
		tmp = open(cmd->redir_in, O_RDONLY);
		if (tmp < 0)
		{
			print_error_acces(cmd->redir_in);
			return (1);
		}
		dup2(tmp, STDIN_FILENO);
		close(tmp);
	}
	return (0);
}

int	msh_redir_out(t_msh_cmd *cmd)
{
	int	tmp;

	if (cmd->redir_out != NULL && cmd->type_out == 1)
	{
		tmp = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp < 0)
		{
			print_error_acces(cmd->redir_out);
			return (1);
		}
		dup2(tmp, STDOUT_FILENO);
		close(tmp);
	}
	return (0);
}

int	msh_redir_append(t_msh_cmd *cmd)
{
	int	tmp;

	if (cmd->append_out != NULL && cmd->type_out == 2)
	{
		tmp = open(cmd->append_out, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (tmp < 0)
		{
			print_error_acces(cmd->append_out);
			return (1);
		}
		dup2(tmp, STDOUT_FILENO);
		close(tmp);
	}
	return (0);
}
