/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:38 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/23 15:57:06 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void count_steps(t_data *data)
{
    static int i;

    data->steps = i;
    data->steps++;
    printf ("steps : %d", data->steps);
}
int	ft_check_format(t_data *data)
{
	int		y;
	int		x;
	int		count_x;

	x = 0;
	y = 0;
	count_x = 0;
	while (data->map[0][count_x])
		count_x++;
	while (data->map[y] != NULL)
	{
		while (data->map[y][x])
			x++;
		if (x != count_x)
		{
			printf("Error\nMap must be a rectangle or a square\n");
			return (0);
		}
		x = 0;
		y++;
	}
	return (1);
} 

int	ft_check_col(t_data *data)
{
    int count = 0;
    int y;
    int x;
    
    count = 0;
    y = 0;
    x = 0;
    while (y < data->map_height) 
    {
        x = 0;
        while ( x < data->map_width) 
        {
            if (data->map[y][0] != '1' || data->map[y][data->map_width - 1] != '1' ||
                data->map[data->map_height - 1][x] != '1' || data->map[0][x] != '1')

            {  
                printf("Error\nMap column not close\n");
                return (1);
            }
            x++;
        }
        y++;
    }
	return (0);
}
int ft_count_map_parameters(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < data->map_height) 
    {
        x = 0;
        while (x < data->map_width) 
        {
            if (data->map[y][x] == 'E') 
                data->exit = 1;
            else if (data->map[y][x] == 'C') 
                data->collectibles = 1;
            else if (data->map[y][x] == 'P') 
                data->player = 1;
            x++;
        }
        y++;
    }
    if (data->exit == 0 || data->collectibles == 0 || data->player == 0)
    {
        printf("Erreur : il manque un élément dans la carte.\n");
        return 1; // Indique qu'il y a une erreur
    }
    return 0; // Tout est bon
}
