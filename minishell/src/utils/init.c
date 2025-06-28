/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:26:00 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/21 01:56:43 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_disable_sigquit(void)
{
	struct termios	terminal;

	if (tcgetattr(STDIN_FILENO, &terminal) == -1)
		return (1);
	terminal.c_cc[VQUIT] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) == -1)
		return (1);
	signal(SIGQUIT, &msh_sig_handler);
	return (0);
}

char	*get_env_key(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=' && env_var[i] != '\0')
		i++;
	if (env_var[i] == '\0')
		return (ft_strdup(env_var));
	return (sub_str(env_var, 0, i));
}

char	*get_env_val(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=' && env_var[i] != '\0')
		i++;
	if (env_var[i] == '\0')
		return (NULL);
	return (ft_strdup(&env_var[i + 1]));
}

static void	increase_shlvl(t_msh_ctx *ctx)
{
	char		*shlvl;
	int64_t		shlvl_val;

	shlvl = msh_get_env(ctx, "SHLVL", NULL);
	if (shlvl == NULL)
		return (msh_set_env(ctx, "SHLVL", "1"));
	if (ft_atoi(shlvl, &shlvl_val))
		return (msh_set_env(ctx, "SHLVL", "1"));
	shlvl_val++;
	shlvl = ft_itoa(shlvl_val);
	msh_set_env(ctx, "SHLVL", shlvl);
	free(shlvl);
}

void	msh_init(char **env, t_msh_ctx *ctx)
{
	msh_disable_sigquit();
	if (signal(SIGINT, &msh_sig_handler) == SIG_ERR)
		exit(1);
	msh_init_ctx(ctx);
	parse_env(env, ctx);
	increase_shlvl(ctx);
}
