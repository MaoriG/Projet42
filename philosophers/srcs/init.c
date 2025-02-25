/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:53:26 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/24 16:05:19 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int p_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->second_fork = &forks[p_position];
	philo->first_fork = &forks[(p_position + 1) % philo_nbr];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[p_position];
		philo->second_fork = &forks[(p_position + 1) % philo_nbr];
	}
}
static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;
	
	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}
void	data_init(t_table *table)
{
	if (!table)
		error_exit("Table is NULL");
	int i;

	i = -1;
	table->threads_running_nbr = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	table->philos = safe_malloc(sizeof(t_philo) * (table->philo_nbr));
	if (!table->philos)
		error_exit("FAILED MEM PHILOS");
	table->forks = safe_malloc(sizeof(t_fork) * (table->philo_nbr));
		if (!table->forks)
		error_exit("FAILED MEM FORKS");
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}