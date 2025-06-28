/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:02:59 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/19 18:02:21 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redir_1(char **redir, const char *value, t_msh_cmd *cmd, int is_in)
{
	free(*redir);
	*redir = ft_strdup(value);
	if (is_in)
		cmd->type_in = 1;
	else
		cmd->type_out = 1;
}

int	set_redir_2(char *value, t_msh_cmd *cmd, int is_in, t_msh_ctx *ctx)
{
	if (is_in)
	{
		free(cmd->here_doc);
		cmd->here_doc = ft_strdup(value);
		cmd->type_in = 2;
		return (msh_get_heredoc(cmd, ctx));
	}
	else
	{
		cmd->type_out = 2;
		free(cmd->append_out);
		cmd->append_out = ft_strdup(value);
	}
	return (0);
}
