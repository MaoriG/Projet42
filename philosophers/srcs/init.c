/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:53:26 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/10 19:59:24 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	data_init (t_table *table)
{
	table->end_simulation = false;
	table->philos = safe_malloc(table->philo_nbr);
	
}