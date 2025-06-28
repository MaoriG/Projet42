/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:32:13 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/22 19:15:28 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int	g_last_signal = 0;

void	msh_sig_handler(int signum)
{
	g_last_signal = signum;
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		is_executing(0, 0);
		rl_redisplay();
	}
}
