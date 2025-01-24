/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:21:53 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/24 23:28:37 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	steps_track(t_data *data)
{
	data->steps++;
	ft_printf("steps: %d\n", data->steps);
}

bool	check_accessibility(t_data *data)
{
	bool	**visited;
	bool	accessible;
	int		i;

	i = 0;
	visited = malloc(data->map_height * sizeof(bool *));
	if (!visited)
		return (false);
	while (i < data->map_height)
	{
		visited[i] = malloc(data->map_width * sizeof(bool));
		if (!visited[i])
		{
			free_visited(data, visited, 0);
			return (false);
		}
		i++;
	}
	init_visited(data, visited, 0);
	find_player_position(data);
	flood_fill(data, data->player_x, data->player_y, visited);
	print_visited(data, visited);
	accessible = are_elements_accessible(data, visited, 0, 0);
	free_visited(data, visited, 0);
	return (accessible);
}
