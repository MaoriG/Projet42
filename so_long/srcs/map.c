/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:10:11 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/18 18:45:25 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"


int get_map_size(const char *filename)
{
    FILE *file;
    int lines = 0;
    char c;

    file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return -1;
    }

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

// Fonction pour lire une ligne du fichier sans le retour à la ligne

char *read_line(FILE *file)
{
    char *line;
    int i;
    char c;

    line = NULL;
    i = 0;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        char *new_line = realloc(line, (i + 2) * sizeof(char));
        if (!new_line) { 
            free(line);
            perror("Erreur d'allocation mémoire");
            return NULL;
        }
        line = new_line;
        line[i++] = c;
    }

    if (line) {
        line[i] = '\0';  // Ajouter un \0 pour marquer la fin de la chaîne
    }
    return line;
}
// Fonction qui lit le fichier et charge la carte dans un tableau de chaînes
char **read_map(const char *filename, int map_size)
{
    FILE *file;
    char **map;
    int i;

    file = fopen(filename, "r");
    map = malloc((map_size + 1) * sizeof(char *));
    if (!file || !map) {
        perror("Erreur d'ouverture ou d'allocation mémoire");
        return NULL;
    }

    for (i = 0; i < map_size; i++) {
        map[i] = read_line(file);
        if (!map[i]) {
            fclose(file);
            return NULL;
        }
    }
    map[i] = NULL;
    fclose(file);
    return map;
}
// Initialisation de la carte dans la structure de données
int init_map(t_data *data, const char *map_file)
{
    FILE *file = fopen(map_file, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    // Compter le nombre de lignes
    int map_size = 0;
    char *line;
    while ((line = read_line(file))) {
        free(line); // Libérer la mémoire de la ligne lue
        map_size++;
    }
    rewind(file);  // Remettre le curseur au début du fichier pour le lire à nouveau

    // Allouer la mémoire pour la carte
    data->map = malloc(sizeof(char *) * (map_size + 1));  // +1 pour le dernier NULL
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
                return 0;  // Le joueur a été trouvé, on peut quitter la fonction
            }
        }
    }

    return 0;  // Le joueur n'a pas été trouvé (cas exceptionnel)
}

// Fonction pour dessiner la carte à l'écran
void draw_map(t_data *data)
{
    int x, y;
    y = 0;
    while (data->map[y]) {
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

