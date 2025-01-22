/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:19:21 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/22 12:19:57 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int load_map_data(t_data *data, const char *map_file)
{
    FILE *file = fopen(map_file, "r");
    if (!file) { perror("Erreur d'ouverture du fichier"); return 1; }

    int map_size = 0;
    char *line;
    while ((line = read_line(file))) { free(line); map_size++; }
    rewind(file);

    data->map = malloc(sizeof(char *) * (map_size + 1));
    if (!data->map) { fclose(file); perror("Erreur d'allocation mémoire"); return 1; }

    int i = 0;
    while ((data->map[i] = read_line(file))) i++;
    fclose(file);

    data->map_width = strlen(data->map[0]);
    data->map_height = map_size;
    return 0;
}

int find_player_and_collectibles(t_data *data)
{
    int y = 0, x = 0;
    while (y < data->map_height) {
        x = 0;
        while (x < data->map_width) {
            if (data->map[y][x] == 'P') { data->player_x = x; data->player_y = y; return 0; }
            x++;
        }
        y++;
    }
    data->collectibles_left = count_collectibles(data);
    return 0;
}

void draw_map(t_data *data)
{
    int x, y;
    y = 0;
    while (data->map[y]) 
    {
        x = 0;
        while (data->map[y][x]) {
            if (data->map[y][x] == '1')
                init_image(data, '1');
            else if (data->map[y][x] == '0')
                init_image(data, '0');
            else if (data->map[y][x] == 'C')
                init_image(data, 'C');
            else if (data->map[y][x] == 'E')
                init_image(data, 'E');
            else if (data->map[y][x] == 'P')
                init_image(data, 'P');
            
            int pixel_x = x * 100;
            int pixel_y = y * 100;
            mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, pixel_x, pixel_y);
            x++;
        }
        y++;
    }
}
int count_collectibles(t_data *data)
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
            if (data->map[y][x] == 'C')
                count++;
            x++;
        }
        y++;
    }
    return count;
}