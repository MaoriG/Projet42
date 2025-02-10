/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:40:08 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/10 19:46:26 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static inline bool is_space (char c)
{
	return (c > 9 && c <= 13 || c == 32);
}

static const char *valid_input(const char *str)
{
	int	len;
	const char *number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
		error_exit("only positive values");
	if (!ft_isdigit(*str))
		error_exit("only digit values");
	number = str;
	while (ft_isdigit(*str++))
		len++;
	if (len > 10)
		error_exit("The value is too big");
	return (number);	
}
static long	ft_atol(const char *str)
{
	long	result;
	
	result = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		result = result * 10 + (*str++ - '0');
	if (result > INT_MAX)
		error_exit("The value is too big");
	return (result);
}
void	parse_input (t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
	|| table->time_to_eat < 6e4)
	error_exit("Use timestamps majour than 60ms");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}
