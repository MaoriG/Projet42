/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:10:29 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/23 19:32:17 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int calculate_new_position(int keysym, t_data *data, int *new_x, int *new_y)
{
    *new_x = data->player_x;
    *new_y = data->player_y;

    if (keysym == 119)
        (*new_y)--;
    else if (keysym == 97)
        (*new_x)--;
    else if (keysym == 115)
        (*new_y)++;
    else if (keysym == 100)
        (*new_x)++;

    return 0;
}
int update_player_position(int new_x, int new_y, t_data *data)
{
    data->collectibles_left = count_collectibles(data);
    if (new_x >= 0 && new_x < data->map_width && new_y >= 0 && new_y < data->map_height)
    {
        if (data->map[new_y][new_x] == '0' || data->map[new_y][new_x] == 'C' || (data->map[new_y][new_x] == 'E' && !count_collectibles(data)) )
        {
            if (data->map[new_y][new_x] == 'E' && !count_collectibles(data))
            {
                printf("You win! You've collected all the items and reached the exit.\n");
                mlx_destroy_window(data->mlx_ptr, data->win_ptr);
                exit(0);
            }
            else if (data->map[new_y][new_x] == 'C') 
            {
                data->collectibles_left--;
                printf("Collectible collected, remaining: %d\n", data->collectibles_left);
            }
            data->map[data->player_y][data->player_x] = '0';
            data->map[new_y][new_x] = 'P';
            data->player_x = new_x;
            data->player_y = new_y;
        }
    }
    data->steps++;
    printf("steps: %d\n", data->steps);
    return 0;
}
int handle_keypress(int keysym, t_data *data)
{
    int new_x;
    int new_y;
    if (keysym == 65307) 
    { 
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        exit(0);
    }
    calculate_new_position(keysym, data, &new_x, &new_y);
    update_player_position(new_x, new_y, data);
    draw_map(data);
    return 0;
}

int on_destroy(t_data *data)
{
    // Libérer la mémoire de la carte
    if (data->map) {
        for (int i = 0; i < data->map_height; i++) {
            free(data->map[i]);
        }
        free(data->map);
    }

    // Libérer la mémoire de mlx
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);

    exit(0);
    return (0);
}