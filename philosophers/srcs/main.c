/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:57:43 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/10 18:39:24 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int main (int ac, char **av)
{
    t_table table;
    
    if (ac == 5 || ac == 6)
    {
        parse_input (&table, av);
        data_init (&table);
        dinner_start(&table);
        clean(&table);
    }
    else
    {
        error_exit("Wrong input\n"
        GREEN"correct is ./philo 2 800 200 200 [5]");
    }
}