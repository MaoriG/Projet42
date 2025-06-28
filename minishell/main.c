/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:27:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/21 01:46:25 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_heredoc(t_msh_cmd *cmds, int cmds_len)
{
	int	i;

	i = 0;
	while (i < cmds_len)
	{
		if (cmds[i].type_in == 2 && cmds[i].here_doc == NULL)
			cmds[i].here_doc = ft_strdup("");
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_msh_ctx	ctx;
	char		*input;
	t_msh_cmd	*cmds;
	int			cmds_len;

	(void)argc;
	(void)argv;
	msh_init(env, &ctx);
	print_banner();
	while (1)
	{
		input = msh_get_input(&ctx);
		if (!input)
			break ;
		g_last_signal = 0;
		cmds_len = parse_pipeline(input, &cmds, &ctx);
		free(input);
		fix_heredoc(cmds, cmds_len);
		msh_exec(&ctx, cmds, cmds_len);
		ctx.last_status = WEXITSTATUS(ctx.last_status);
		ctx.last_status = ctx.last_status % 256;
	}
	rl_clear_history();
	msh_free_ctx(&ctx);
	return (0);
}
