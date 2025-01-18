/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:19:21 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/18 17:21:14 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int verif_map (t_data *data)
{
    char **str;
    int i;
    int j;

    i = 0;
    j = 0;
    str = data->map;
    while (str[i])
    {
        j = 0;
            while (str[i][j])
            {
            if (str[i][j] != '0' && str[i][j] != '1' && str[i][j] != 'E' && 
            str[i][j] != 'P' && str[i][j] != 'C')
            return (0);
            j++;
            }
        i++;
    }
    return (1);
}

void free_map(t_data *data) 
{
    if (data->map) {
        for (int i = 0; data->map[i] != NULL; i++) {
            free(data->map[i]);
        }
        free(data->map);
    }
}

/* char **read_map(const char *filename, int map_size)
{
    FILE *file;
    char **map;
    int i;

    file = fopen(filename, "r");
    map = malloc((map_size + 1) * sizeof(char *));
    i = 0;
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }
    while (i < map_size) {
        map[i] = read_line(file);
        if (!map[i]) {
            fclose(file);
            return NULL;
        }
        i++;
    }
    map[i] = NULL;
    fclose(file);
    return map;
} */