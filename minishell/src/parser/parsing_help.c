/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:23:50 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/20 03:16:45 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	only_spaces(const char *line)
{
	while (*line)
	{
		if (!isspace((unsigned char)*line))
			return (0);
		line++;
	}
	return (1);
}

void	update_quote(char c, char *quote)
{
	if (!quote)
		return ;
	if ((*quote == 0) && (c == '\'' || c == '"'))
		*quote = c;
	else if (c == *quote)
		*quote = 0;
}

int	skip_spaces(const char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}
