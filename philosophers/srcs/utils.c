/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:51 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/10 18:25:04 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void    error_exit(const char *error)
{
	ft_printf(RED"🚨 %s 🚨\n", error);
	exit(EXIT_FAILURE);
}