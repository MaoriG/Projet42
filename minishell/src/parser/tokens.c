/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:03:29 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 19:04:24 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_token_squoted(char *line, int *i)
{
	char	*token;
	int		start;
	int		len;

	start = ++(*i);
	while (line[*i] != '\'' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
		return (NULL);
	len = *i - start;
	if (len == 0)
		token = ft_strdup("");
	else
		token = ft_substr(line, start, len);
	(*i)++;
	return (token);
}

static char	*get_token_dquoted(char *line, int *i)
{
	char	*token;
	int		start;
	int		len;

	start = ++(*i);
	while (line[*i] != '\"' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
		return (NULL);
	len = *i - start;
	if (len == 0)
		token = ft_strdup("");
	else
		token = ft_substr(line, start, len);
	(*i)++;
	return (token);
}

static char	*get_next_token(char *line, int *i)
{
	char	*token;
	int		start;
	int		len;

	if (line[*i] == '\'')
		token = get_token_squoted(line, i);
	else if (line[*i] == '\"')
		token = get_token_dquoted(line, i);
	else if (line[*i] == '<' || line[*i] == '>')
		token = get_token_redir(line, i);
	else
	{
		start = *i;
		while (!ft_is_space(line[*i]) && line[*i] != '\0' && line[*i] != '\"'
			&& line[*i] != '\'' && line[*i] != '<' && line[*i] != '>')
			(*i)++;
		len = *i - start;
		token = ft_substr(line, start, len);
	}
	return (token);
}

static char	*add_type(char *token, int is_op)
{
	char	*res;
	int		i;

	if (token == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(token) + 2));
	res[ft_strlen(token) + 1] = is_op;
	i = 0;
	while (token[i] != '\0')
	{
		res[i] = token[i];
		i++;
	}
	res[i] = '\0';
	free(token);
	return (res);
}

void	append_token(char **res, int *res_len, char *line, int *i)
{
	char	*token;
	int		old_i;
	char	*tmp;

	old_i = *i;
	token = get_next_token(line, i);
	if (line[old_i] == '<' || line[old_i] == '>')
	{
		res[(*res_len)++] = add_type(token, 1);
		return ;
	}
	if (old_i - 1 >= 0 && !ft_is_space(line[old_i - 1]) && *res_len > 0
		&& !is_op(res[(*res_len) - 1]))
	{
		tmp = res[(*res_len) - 1];
		res[(*res_len) - 1] = add_type(ft_strjoin(tmp, token), 0);
		free(tmp);
		free(token);
	}
	else
		res[(*res_len)++] = add_type(token, 0);
}
