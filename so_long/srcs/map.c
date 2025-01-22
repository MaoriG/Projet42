/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:10:11 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/22 12:52:21 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int get_map_size(const char *filename)
{
    FILE *file;
    int lines = 0;
    char c;

    file = fopen(filename, "r");
    if (!file) 
    {
        perror("Erreur d'ouverture du fichier");
        return -1;
    }
    while ((c = fgetc(file)) != EOF) 
    {
        if (c == '\n')
            lines++;
    }
    fclose(file);
    return lines;
}

char *read_line(FILE *file)
{
    char *line;
    int i;
    char c;

    line = NULL;
    i = 0;
    while ((c = fgetc(file)) != EOF && c != '\n') 
    {
        char *new_line = realloc(line, (i + 2) * sizeof(char));
        if (!new_line) 
        { 
            free(line);
            perror("Erreur d'allocation mémoire");
            return NULL;
        }
        line = new_line;
        line[i++] = c;
    }
    if (line)
        line[i] = '\0';
    return line;
}
int read_map_file(t_data *data, const char *map_file)
{
    FILE *file;
    int map_size;
    char *line;
    int i;
    
    file = fopen(map_file, "r");
    map_size = 0;
    line = NULL;
    i = 0;
    if (!file) { perror("Erreur d'ouverture du fichier"); return 1; }
    while ((line = read_line(file))) { free(line); map_size++; }
    rewind(file);
    data->map = malloc(sizeof(char *) * (map_size + 1));
    if (!data->map) { fclose(file); perror("Erreur d'allocation mémoire"); return 1; }
    while ((data->map[i] = read_line(file))) i++;
    data->map[i] = NULL;
    fclose(file);
    data->map_width = strlen(data->map[0]);
    data->map_height = map_size;
    return 0;
}
int initialize_game(t_data *data)
{
    int y = 0, x = 0;
    
    // Trouve la position du joueur
    while (y < data->map_height) {
        x = 0;
        while (x < data->map_width) {
            if (data->map[y][x] == 'P') 
            { 
                data->player_x = x; 
                data->player_y = y; 
                break;
            }
            x++;
        }
        if (x < data->map_width) break; // Trouvé
        y++;
    }
    // Initialiser les autres éléments du jeu comme les collectibles
    data->collectibles_left = count_collectibles(data);
    data->steps = 0;

    return 0;
}

int init_map(t_data *data, const char *map_file)
{
    if (read_map_file(data, map_file))
        return (1);
    if (!is_accessible(data))
        return (1);
    if (initialize_game(data))
        return (1);
    if (load_map_data(data, map_file))
        return (1);
    if (find_player_and_collectibles(data))
        return (1);
    return 0;
}
