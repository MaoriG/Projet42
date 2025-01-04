/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 00:47:14 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/04 17:31:15 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	Kill(pid_t pid, int signo)
{
	if (kill(pid, signo) < 0)
	{
		perror("Kill failed");
		exit(EXIT_FAILURE);
	}
}
void	Signal(int signo, void *handler, bool use_siginfo)
{
	struct sigaction sa = {0};
	if (use_siginfo)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
	}
	else
		sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(signo, &sa, NULL) < 0)
	{
		perror("Sigaction failed");
		exit(EXIT_FAILURE);
	}
}
