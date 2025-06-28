/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilshelp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:56:44 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/18 16:36:19 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n'
			&& *line != '\r' && *line != '\v' && *line != '\f')
			return (0);
		line++;
	}
	return (1);
}
