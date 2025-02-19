/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:12:22 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/19 18:15:23 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void set_bool(t_mtx *mutex, bool *dest, bool value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

bool    get_bool(t_mtx *mutex, bool *value)
{
    bool ret;

    if (!mutex || !value)
        error_exit("invalid mutex or value pointer");
    safe_mutex_handle(mutex, LOCK);
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return(ret);
}
long get_long(t_mtx *mutex, long *value)
{
    long ret;

    safe_mutex_handle(mutex, LOCK);
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return (ret);
}

void set_long(t_mtx *mutex, long *dest, long value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}
bool simulation_finished(t_table *table)
{
    return (get_bool(&table->table_mutex, &table->end_simulation));
}   