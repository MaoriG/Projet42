/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:52:04 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/23 19:46:34 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int		directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

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
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height
		|| visited[y][x] || data->map[y][x] == '1')
		return ;
	visited[y][x] = true;
	printf("Exploration: (%d, %d) -> %c\n", x, y, data->map[y][x]);
	for (int i = 0; i < 4; i++)
	{
		flood_fill(data, x + directions[i][0], y + directions[i][1], visited);
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
void free_visited(t_data *data, bool **visited, int y)
{
    if (y == data->map_height) {
        free(visited);
        return;
    }
    free(visited[y]);
    free_visited(data, visited, y + 1);
}

void	print_visited(t_data *data, bool **visited)
{
    int y;
    int x;

    y = 0;
    x = 0;
    
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			printf("%c ", visited[y][x] ? 'X' : 'O');
            x++;
		}
        y++;
		printf("\n");
	}
}

bool	are_elements_accessible(t_data *data, bool **visited, int y, int x)
{
	if (y == data->map_height)
		return (true);
	if (x == data->map_width)
		return (are_elements_accessible(data, visited, y + 1, 0));
	printf("Vérification à (%d, %d): %c\n", x, y, data->map[y][x]);
	if ((data->map[y][x] == 'C' || data->map[y][x] == 'E') && !visited[y][x])
	{
		printf("Erreur : élément inaccessible à la position (%d, %d)\n", x, y);
		return (false);
	}
	return (are_elements_accessible(data, visited, y, x + 1));
}

bool check_accessibility(t_data *data)
{
    bool **visited;
    bool accessible;
    int i;

    i = 0;
    visited = malloc(data->map_height * sizeof(bool *));
    if (!visited)
        return false;
    while (i < data->map_height) {
        visited[i] = malloc(data->map_width * sizeof(bool));
        if (!visited[i]) {
            free_visited(data, visited, 0);
            return false;
        }
        i++;
    }

    init_visited(data, visited, 0);
    find_player_position(data);
    flood_fill(data, data->player_x, data->player_y, visited);
    print_visited(data, visited);
    accessible = are_elements_accessible(data, visited, 0, 0);
    free_visited(data, visited, 0);  // Libérer la mémoire après utilisation
    return accessible;
}
