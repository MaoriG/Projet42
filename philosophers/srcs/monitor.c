/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:45:23 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/25 18:09:00 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static bool philo_died(t_philo *philo)
{
    long elapsed;
    long t_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    elapsed = (gettime(MILLISECOND) - 
    get_long(&philo->philo_mutex, &philo->last_meal_time));
    t_to_die = (philo->table->time_to_die / 1e3);
    if (elapsed > t_to_die)
        return (true);
    return (false);
}

void	*monitor_dinner(void *data)
{
    int i;
	t_table *table;

	table = (t_table *)data;
    i = 0;
	while (!all_threads_running(&table->table_mutex, &table->threads_running_nbr,
			table->philo_nbr))
		;
    while (!simulation_finished(table))
    {
        i = -1;
        while (++i < table->philo_nbr && !simulation_finished(table))
        {
            if (philo_died(table->philos + i))
            {
                set_bool(&table->table_mutex, &table->end_simulation, true);
                write_status(DIED, table->philos + i, DEBUG_MODE);
            }
        }
    }
	return (NULL);
}