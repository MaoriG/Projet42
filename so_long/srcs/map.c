/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:10:11 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/21 17:43:34 by mgobert          ###   ########.fr       */
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

int init_map(t_data *data, const char *map_file)
{
    FILE *file = fopen(map_file, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }
    int map_size = 0;
    char *line;
    while ((line = read_line(file))) 
    {
        free(line);
        map_size++;
    }
    rewind(file);
    data->map = malloc(sizeof(char *) * (map_size + 1));
    if (!data->map) {
        fclose(file);
        perror("Erreur d'allocation mémoire");
        return 1;
    }
    // Lire la carte ligne par ligne
    int i = 0;
    while ((data->map[i] = read_line(file))) {
        i++;
    }
    fclose(file);

    // Calculer les dimensions de la carte
    data->map_width = strlen(data->map[0]);
    data->map_height = map_size;

    // Trouver la position initiale du joueur (P)
    for (int y = 0; y < data->map_height; y++) {
        for (int x = 0; x < data->map_width; x++) {
            if (data->map[y][x] == 'P') {
                data->player_x = x;
                data->player_y = y;
                break;
            }
        }
    }

    // Compter les collectibles uniquement lors de l'initialisation
    data->collectibles_left = count_collectibles(data);

    return 0;
}
void check_and_place_exit(t_data *data)
{
    int y = 0;
    int x = 0;
    if (data->collectibles_left == 0 && !data->collectibles_collected) {
        // Si tous les collectibles sont collectés mais que l'exit n'est pas encore placé
        bool exit_found = false;
        
        // Vérifier si l'exit est déjà placé
        for (y = 0; y < data->map_height; y++) {
            for (x = 0; x < data->map_width; x++) {
                if (data->map[y][x] == 'E') {
                    exit_found = true;
                    break;
                }
            }
            if (exit_found) break;
        }

        // Si l'exit n'a pas encore été placé
        if (!exit_found) {
            // Placer l'exit à la première position libre
            for (y = 0; y < data->map_height; y++) {
                for (x = 0; x < data->map_width; x++) {
                    if (data->map[y][x] == '0') {
                        data->map[y][x] = 'E';  // Placer l'exit
                        printf("Exit placed at (%d, %d)\n", x, y);
                        break;
                    }
                }
                if (data->map[y][x] == 'E') break;
            }
        }
    }
}


// Fonction pour dessiner la carte à l'écran
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

