/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:55:38 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/16 16:07:14 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	if (status == EAGAIN)
		error_exit("No ressources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have permission");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid");
	else if (status == EINVAL && (opcode == JOIN ||opcode == DETACH))
		error_exit("The value specified ny thread is mnot joinable");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that"
		"speicified by the given thread ID, thread");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of"
		"thread specifies the calling thread");
}
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
 t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else 
		error_exit("Wrong opcode for thread_handle"
		"use <CREATE> <JOIN> <DETACH>");
}

void	*safe_malloc(size_t bytes)
{
	void *ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error with the malloc");
	return (ret);
}
static void handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specifie by mutex is invalid");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("DEADL would occur if the thread block witing for mutex");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_exit("Process cannot allocate enough mem to for another mutex");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

void safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else 
		error_exit("Wong opcode for mutex handle");
}
