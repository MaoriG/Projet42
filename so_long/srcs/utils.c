/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:52:04 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/25 00:02:36 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	find_player_position(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	flood_fill(t_data *data, int x, int y, bool **visited)
{
	int	i;
	int	directions[4][2];

	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = 0;
	directions[3][1] = 1;
	i = 0;
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height
		|| visited[y][x] || data->map[y][x] == '1')
		return ;
	visited[y][x] = true;
	while (i < 4)
	{
		flood_fill(data, x + directions[i][0], y + directions[i][1], visited);
		i++;
	}
}

void	init_visited(t_data *data, bool **visited, int y)
{
	int	x;

	x = 0;
	if (y == data->map_height)
		return ;
	while (x < data->map_width)
	{
		visited[y][x] = false;
		x++;
	}
	init_visited(data, visited, y + 1);
}

void	print_visited(t_data *data, bool **visited)
{
	int			y;
	int			x;
	char		symbol;

	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			if (visited[y][x])
				symbol = 'X';
			else
				symbol = 'O';
			ft_printf("%c", symbol);
			x++;
		}
		y++;
		ft_printf("\n");
	}
}

bool	are_elements_accessible(t_data *data, bool **visited, int y, int x)
{
	if (y == data->map_height)
		return (true);
	if (x == data->map_width)
		return (are_elements_accessible(data, visited, y + 1, 0));
	if ((data->map[y][x] == 'C' || data->map[y][x] == 'E') && !visited[y][x])
	{
		ft_printf("Error\npath not found (%d, %d)\n", x, y);
		return (false);
	}
	return (are_elements_accessible(data, visited, y, x + 1));
}
