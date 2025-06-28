/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:49:58 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/18 15:31:27 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_msh_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->env_len)
	{
		if (ctx->env[i].value)
			printf("%s=%s\n", ctx->env[i].name, ctx->env[i].value);
		i++;
	}
	return (0);
}

int	builtin_unset(int argc, char **argv, t_msh_ctx *ctx)
{
	int	i;

	(void)argc;
	(void)argv;
	i = 1;
	while (i < argc)
	{
		msh_unset_env(ctx, argv[i]);
		i++;
	}
	return (0);
}
