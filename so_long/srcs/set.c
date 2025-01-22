/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:38 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/22 12:49:51 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int is_accessible(t_data *data)
{
    int y;
    int x;
    
    y = 0;
    x = 0;
    while (y < data->map_height) 
    {
        x = 0;
        while ( x < data->map_width) 
        {
            if (data->map[y][x] == 'C')
            {
                if (!verif_access(data, y, x))
                    return (0);
            }
            if (data->map[y][x] == 'P')
            {
                if (!verif_access(data, y, x))
                    return (0);
            }
            if (data->map[y][x] == 'E')
            {
                if (!verif_access(data, y, x))
                    return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}
int verif_access (t_data *data, int y, int x)
{
    if (data->map[y + 1][x] == '1' && data->map[y - 1][x] == '1' && data->map[y][x + 1] == '1'
    && data->map[y][x - 1] == '1')
    {
        printf("Error invalid map");
        return (0);
    }
    else 
        return(1);
}

void count_steps(t_data *data)
{
    static int i;

    data->steps = i;
    data->steps++;
    printf ("setps : %d", data->steps);
}