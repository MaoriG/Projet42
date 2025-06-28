/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:34:49 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/19 19:21:36 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_assemble_path(char *p1, char *p2)
{
	int		p1_len;
	int		p2_len;
	char	*res;

	p1_len = ft_strlen(p1);
	p2_len = ft_strlen(p2);
	res = safe_malloc(sizeof(char) * (p1_len + p2_len + 1 + 1));
	ft_strcpy(res, p1);
	res[p1_len] = '/';
	ft_strcpy(&(res[p1_len + 1]), p2);
	res[p1_len + p2_len + 1] = '\0';
	return (res);
}
