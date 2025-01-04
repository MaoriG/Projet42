/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 00:03:40 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/04 17:27:56 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_server = BUSY;

void	end_handler(int signo)
{
	write(1, "ok!", 3);
	exit(EXIT_SUCCESS);
}
void	ack_handler(int signo)
{
	g_server = READY;
}
void	send_char(char c, pid_t server)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (c & (0b10000000) >> bit)
			Kill(server, SIGUSR1);
		else
			Kill(server, SIGUSR2);
		bit++;
		while (g_server == BUSY)
			usleep(42);
		g_server = BUSY;
	}
}

int	main(int ac, char **av)
{
	pid_t server;
	char *message;

	if (ac != 3)
	{
		fputs("Usage = ./client <PID> \"Message\"\n", stderr);
		exit(EXIT_FAILURE);
	}
	server = atoi(av[1]);
	message = av[2];

	Signal(SIGUSR1, ack_handler, false);
	Signal(SIGUSR2, end_handler, false);
	while (*message)
		send_char(*message++, server);
	send_char('\0', server);
	return (EXIT_SUCCESS);
}
