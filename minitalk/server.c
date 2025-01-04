/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 00:03:42 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/04 17:31:28 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * handler - Processes incoming signals to reconstruct characters
 * @sig: Signal type (SIGUSR1 or SIGUSR2)
 * @info: Signal information containing sender's PID
 * @more_info: Additional context (unused)
 * Note: Uses static variables to maintain state between signal calls
 */
#include "minitalk.h"

void	handler(int signo, siginfo_t *info, void *more_info)
{
	static char		c;
	static int		bit;
	static pid_t	client;

	if (info->si_pid)
		client = info->si_pid;
	(void)more_info;
	client = info->si_pid;
	if (SIGUSR1 == signo)
		c |= (0b10000000 >> bit);
	else if (SIGUSR2 == signo)
		c &= ~(0b10000000 >> bit);
	bit++;
	if (CHAR_BIT == bit)
	{
		bit = 0;
		if ('\0' == c)
		{
			write(1, "\n", 1);
			Kill(client, SIGUSR2);
			return ;
		}
		write(1, &c, 1);
	}
	kill(client, SIGUSR1);
}

int	main(void)
{
	printf("server PID=%d\n", getpid());
	Signal(SIGUSR1, handler, true);
	Signal(SIGUSR2, handler, true);
	while (1137)
	{
		pause();
	}

	return (EXIT_SUCCESS);
}
