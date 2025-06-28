/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:28:25 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/20 20:08:13 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_redir(t_msh_cmd *cmd, t_msh_ctx *ctx, char **tokens)
{
	int		i;

	i = -1;
	while (tokens[++i])
	{
		if (!ftstrcmp(tokens[i], "<") && tokens[i + 1] && is_op(tokens[i]))
			set_redir_1(&cmd->redir_in, tokens[++i], cmd, 1);
		else if (!ftstrcmp(tokens[i], ">") && tokens[i + 1]
			&& is_op(tokens[i]))
			set_redir_1(&cmd->redir_out, tokens[++i], cmd, 0);
		else if (!ftstrcmp(tokens[i], ">>") && tokens[i + 1]
			&& is_op(tokens[i]))
			set_redir_2(tokens[++i], cmd, 0, NULL);
		else if (!ftstrcmp(tokens[i], "<<") && tokens[i + 1]
			&& is_op(tokens[i]))
		{
			if (set_redir_2(tokens[++i], cmd, 1, ctx))
				return (free_split(tokens), 1);
		}
		else if (is_op(tokens[i]))
			return (print_error_op(tokens[i]), free_split(tokens), 1);
		else
			cmd->argv[cmd->argc++] = ft_strdup(tokens[i]);
	}
	return (free_split(tokens), 0);
}

int	init_command(char *line, t_msh_cmd *cmd, t_msh_ctx *ctx)
{
	char	**tokens;

	tokens = get_tokens(line, ctx);
	init_tab(cmd);
	cmd->argv = ft_calloc(sizeof(char *), 1 + tab_len(tokens));
	if (tokens && set_redir(cmd, ctx, tokens))
		return (1);
	if (cmd->argv == NULL)
		return (0);
	if (cmd->argc > 0)
		cmd->name = cmd->argv[0];
	else
		cmd->name = NULL;
	return (0);
}

void	init_tab(t_msh_cmd *cmd)
{
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->append_out = NULL;
	cmd->here_doc = NULL;
}
