/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:32:52 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 19:04:32 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_tokens(char *line, t_msh_ctx *ctx)
{
	char	**res;
	int		res_len;
	int		i;

	line = replace_var(ft_strdup(line), ctx);
	if (line == NULL)
		return (NULL);
	res_len = token_count(line);
	if (res_len == -1)
	{
		ctx->last_status = 2;
		return (free(line), NULL);
	}
	res = safe_malloc(sizeof(char *) * (res_len + 1));
	res_len = 0;
	i = 0;
	while (line[i] != '\0')
	{
		while (ft_is_space(line[i]))
			i++;
		if (line[i] != '\0')
			append_token(res, &res_len, line, &i);
	}
	res[res_len] = NULL;
	return (free(line), res);
}

char	*get_token_redir(char *line, int *i)
{
	char	*token;
	int		start;
	int		len;

	start = *i;
	while (line[*i] == '>' || line[*i] == '<')
		(*i)++;
	len = *i - start;
	token = ft_substr(line, start, len);
	return (token);
}

int	is_op(char *tok)
{
	return (tok[ft_strlen(tok) + 1] != '\0');
}
