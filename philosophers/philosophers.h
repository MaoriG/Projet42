/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:14:29 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/16 15:38:07 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "./printf/ft_printf.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
#include <errno.h>

# define RST 		"0\33[0m"
# define RED 		"\033[1;31m"
# define GREEN 		"\033[1;32m"
# define YELLOW 	"\033[1;33m"
# define BLUE 		"\033[1;34m"
# define MAGENTA 	"\033[1;35m"
# define CYAN 		"\033[1;36m"
# define WHITE 		"\033[1;37m"

# define DEBUG_MODE 0

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_time_code;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_table				*table;
	t_mtx				philo_mutex;
}						t_philo;

struct					s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_simulation;
	bool				end_simulation;
	t_fork				*forks;
	t_philo				*philos;
	bool				all_threads_ready;
	t_mtx				table_mutex;
	t_mtx 				write_mutex;
};

void    error_exit(const char *error);
void	parse_input (t_table *table, char **av);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
 t_opcode opcode);
void	*safe_malloc(size_t bytes);
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void set_bool(t_mtx *mutex, bool *dest, bool value);
bool    get_bool(t_mtx *mutex, bool *value);
long get_long(t_mtx *mutex, long *value);
void set_long(t_mtx *mutex, long *dest, long value);
bool simulation_finished(t_table *table);
void wait_all_threads(t_table *table);
long gettime(t_time_code time_code);
void precise_usleep(long usec, t_table *table);
void write_status (t_philo_status status, t_philo *philo, bool debug);
void	data_init(t_table *table);
void    dinner_start(t_table *table);
void    error_exit(const char *error);

#endif