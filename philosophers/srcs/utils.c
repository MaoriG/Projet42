/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:51 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/19 17:54:24 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void    error_exit(const char *error)
{
	ft_printf(RED"🚨 %s 🚨\n", error);
	exit(EXIT_FAILURE);
}

long gettime(t_time_code time_code)
{
	struct timeval tv;
	
	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_sec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else 
		error_exit("Wrong input to gettime");
	return (1337);
}
void precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime (MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break;
		usleep(100);
	}
	elapsed = gettime(MICROSECOND) - start;
	rem = usec - elapsed;
	if (rem > 1e3)
		usleep(usec / 2);
	else
	{
		while (gettime (MICROSECOND) - start < usec)
			;
	}
}