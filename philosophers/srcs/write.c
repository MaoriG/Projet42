/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:23:55 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/16 16:17:45 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void write_status_debug(t_philo_status status, t_philo *philo, 
long elapsed)
{
    if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
        ft_printf(WHITE"%6ld"RST" %d has taken the first fork"
         "\t %d", elapsed, philo->id, philo->first_fork->fork_id);
    else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
        ft_printf(WHITE"%6ld"RST" %d has taken the second fork"
        "\t %d", elapsed, philo->id, philo->second_fork->fork_id);
    else if (status == EATING && !simulation_finished(philo->table))
        ft_printf(WHITE"%6ld"RST" %d is eating"
        "\t %d\n", elapsed, philo->id, philo->meals_counter);
    else if (status == SLEEPING && !simulation_finished(philo->table))
        ft_printf(WHITE"%6ld"RST" %d is sleeping\n", elapsed, philo->id);
    else if (status == THINKING && !simulation_finished(philo->table))
        ft_printf(WHITE"%6ld"RST" %d is thinking\n", elapsed, philo->id);
    else if (status == DIED)
        ft_printf(RED"\t %6ld %d died\n", elapsed, philo->id);
}
void write_status (t_philo_status status, t_philo *philo, bool debug)
{
    long elapsed;

    elapsed = gettime(MILISECOND);
    if (philo->full)
        return;
    safe_mutex_handle(&philo->table->write_mutex, LOCK);
    if (debug)
        write_status_debug(status, philo, elapsed);
    else 
    {
        if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK && 
            !simulation_finished(philo->table))
            ft_printf(WHITE"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
        else if (status == EATING && !simulation_finished(philo->table))
            ft_printf(WHITE"%-6ld"CYAN" %d is eating\n"RST, elapsed, philo->id);
        else if (status == SLEEPING && !simulation_finished(philo->table))
            ft_printf(WHITE"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
        else if (status == THINKING && !simulation_finished(philo->table))
            ft_printf(WHITE"&-6ld"RST" %d is thinking\n", elapsed, philo->id);
        else if (DIED == status)
            ft_printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
            
    }
    safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
    
}