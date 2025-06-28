/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:31:02 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/19 19:19:38 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_count_squoted(char *line, int *i, int *res,
		int *last_token_op)
{
	(*i)++;
	while (line[*i] != '\'' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
	{
		*res = -1;
		return ;
	}
	(*i)++;
	(*last_token_op) = 0;
}

static void	token_count_dquoted(char *line, int *i, int *res,
		int *last_token_op)
{
	(*i)++;
	while (line[*i] != '\"' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
	{
		*res = -1;
		return ;
	}
	(*i)++;
	(*last_token_op) = 0;
}

static void	token_count_redir(char *line, int *i, int *res,
		int *last_token_op)
{
	(*res)++;
	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '>')
		{
			(*res) = -1;
			print_error("minishell: missing redirection\n");
		}
		else if (line[*i] == '<')
			(*i)++;
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '<')
		{
			(*res) = -1;
			print_error("minishell: missing redirection\n");
		}
		else if (line[*i] == '>')
			(*i)++;
	}
	(*last_token_op) = 1;
}

static void	token_count_word(char *line, int *i, int *res,
		int *last_token_op)
{
	(*res)++;
	while (!ft_is_space(line[*i]) && line[*i] != '\0' && line[*i] != '\"'
		&& line[*i] != '\'' && line[*i] != '<' && line[*i] != '>')
		(*i)++;
	(*last_token_op) = 0;
}

int	token_count(char *line)
{
	int	i;
	int	res;
	int	last_token_op;

	i = 0;
	res = 0;
	last_token_op = 0;
	while (line && line[i] != '\0')
	{
		while (ft_is_space(line[i]))
			i++;
		if (line[i] == '\'')
			token_count_squoted(line, &i, &res, &last_token_op);
		else if (line[i] == '\"')
			token_count_dquoted(line, &i, &res, &last_token_op);
		else if (line[i] == '<' || line[i] == '>')
			token_count_redir(line, &i, &res, &last_token_op);
		else if (line[i] != '\0')
			token_count_word(line, &i, &res, &last_token_op);
		if (res == -1)
			return (-1);
	}
	if (last_token_op == 1)
		return (print_error("minishell: missing redirection\n"), -1);
	return (i);
}
