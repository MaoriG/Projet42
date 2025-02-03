/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:14:29 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/03 19:12:06 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include "./printf/ft_printf.h"
#include <stdbool.h>

 typedef	struct        s_arg             //arguments after ./philo
{
	int                   total;            // number of philosophers
	int                   die_time;              // time to die in milliseconds
	int                   eat_time;              // time to eat in milliseconds
	int                   sleep_time;            // time to sleep in milliseconds
	int                   m_eat;            // must eat m_eat times
	long int              start_t;          // start time in milliseconds
	pthread_mutex_t       write_mutex;      // write mutex
	int                   nb_p_finish;      // when a philosopher ate m_eat times : nb_p_finish++
	int                   stop;             // 0 if none philosopher is dead, 1 if a philosopher is dead, 2 if all philosophers ate m_eat times
}                       t_arg;

typedef	struct          s_philo
{
	int                   id;               // id of the philosopher
	pthread_t             thread_id;        // thread id
	pthread_t             thread_death_id;  // id of the thread monitoring death
	pthread_mutex_t       *r_f;             // right fork mutex
	pthread_mutex_t       l_f;              // left fork mutex
	t_arg                 *pa;              // pointer to structure with all arguments (pointer on a)
	long int              ms_eat;           // time of the last dinner in milliseconds
	unsigned int          nb_eat;           // number of dinners (each time the philosopher eats nb_eat++)
	int                   finish;           // 1 when a philosopher ate m_eat times, if not, 0
}                       t_philo;

typedef	struct          s_p
{
	t_philo               *ph;          
	t_arg                 a;                
} 					t_p;

#endif