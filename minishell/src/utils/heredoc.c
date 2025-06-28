/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:29:24 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/21 14:27:00 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	str_append_line(char **dest, char *src, t_msh_ctx *ctx)
{
	char	*new_str;

	if (src == NULL)
		return ;
	src = replace_var(ft_strdup(src), ctx);
	new_str = malloc(ft_strlen(*dest) + 1 + ft_strlen(src) + 2);
	new_str[0] = '\0';
	if (*dest != NULL)
	{
		ft_strcat(new_str, *dest);
		free(*dest);
	}
	ft_strcat(new_str, src);
	ft_strcat(new_str, "\n");
	*dest = new_str;
	free(src);
	return ;
}

int	msh_get_heredoc(t_msh_cmd *cmd, t_msh_ctx *ctx)
{
	char	*input;
	char	*content;

	content = NULL;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			print_error("minishell: warning: here-document end-of-file\n");
			break ;
		}
		if (ftstrcmp(input, cmd->here_doc) == 0)
		{
			free(input);
			break ;
		}
		str_append_line(&content, input, ctx);
		free(input);
	}
	free(cmd->here_doc);
	cmd->here_doc = content;
	return (0);
}
