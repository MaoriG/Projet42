/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:57:43 by mgobert           #+#    #+#             */
/*   Updated: 2025/02/03 19:24:58 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	verif_av(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
				return (ft_printf("Error\nArguments must be a digital"), true);
		}
		i++;
	}
	return (false);
}
void	init_function(int ac, char **av, t_p *p)
{
	if (ac == 5 || ac == 6)
	{
		p->a.total = ft_atoi(av[1]);
		p->a.die_time = ft_atoi(av[2]);
		p->a.eat_time = ft_atoi(av[3]);
		p->a.eat_time = ft_atoi(av[4]);
		p->a.m_eat = -1;
		if (ac == 6)
			p->a.m_eat = ft_atoi(av[5]);
	}
}

void	if_not(void)
{
	ft_printf("the usage of the function is as follows :\n");
	ft_printf("arg1 = number of philosophers and of fourch \n");
	ft_printf("arg2 = time to die (in millisecond)\n");
	ft_printf("arg3 = time to eat (with two fourch)\n");
	ft_printf("arg4 = time to sleep (in milisecond)\n");
	ft_printf("arg5 = number of times each philosopher must eat\n");
	ft_printf("arg6 = numbers of times each philo must eat (optionnal)\n");
}
int	main(int ac, char **av)
{
	t_p p;
	if (ac != 6 && ac != 7)
		return (if_not(), 0);
	if (!verif_av(ac, av))
		init_function(ac, av, &p);
}
