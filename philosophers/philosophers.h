/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:14:29 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/10 20:47:47 by mgobert          ###   ########.fr       */
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

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

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
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_table				*table;
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
};

void    error_exit(const char *error);
void	parse_input (t_table *table, char **av);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
 t_opcode opcode);
void	*safe_malloc(size_t bytes);
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

#endif