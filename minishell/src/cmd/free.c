/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:24:12 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/05 23:23:05 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	msh_free_cmds(t_msh_cmd *cmds, int cmds_len)
{
	int	i;
	int	k;

	i = -1;
	while (++i < cmds_len)
	{
		free(cmds[i].path);
		free(cmds[i].redir_out);
		free(cmds[i].redir_in);
		free(cmds[i].here_doc);
		free(cmds[i].append_out);
		k = -1;
		while (++k < cmds[i].argc)
			free(cmds[i].argv[k]);
		free(cmds[i].argv);
	}
	free(cmds);
}
