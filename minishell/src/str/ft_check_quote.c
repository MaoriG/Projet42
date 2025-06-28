/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:28:16 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/19 20:34:10 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\0' && input[i] != '\'')
				i++;
			if (input[i] == '\0')
				return (print_error("minishell: unclosed quote '\n"), 1);
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] != '\0' && input[i] != '"')
				i++;
			if (input[i] == '\0')
				return (print_error("minishell: unclosed quote \"\n"), 1);
		}
		i++;
	}
	return (0);
}
