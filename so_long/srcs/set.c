/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:38 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/21 17:01:56 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"


// Fonction BFS pour vérifier l'accessibilité
bool is_exit_reachable(t_data *data)
{
    bool **visited = malloc(data->map_height * sizeof(bool *));
    for (int i = 0; i < data->map_height; i++) {
        visited[i] = malloc(data->map_width * sizeof(bool));
        for (int j = 0; j < data->map_width; j++) {
            visited[i][j] = false;
        }
    }

    t_position queue[10000];  // Assurez-vous que cette taille est suffisante
    int front = 0, rear = 0;

    // Enqueue la position initiale du joueur
    queue[rear++] = (t_position){data->player_x, data->player_y};
    visited[data->player_y][data->player_x] = true;

    // Directions possibles (haut, bas, gauche, droite)
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (front < rear) {
        t_position current = queue[front++];

        // Si nous trouvons l'exit
        if (data->map[current.y][current.x] == 'E') {
            for (int i = 0; i < data->map_height; i++) {
                free(visited[i]);
            }
            free(visited);
            return true;
        }

        // Explorer les voisins
        for (int i = 0; i < 4; i++) {
            int new_x = current.x + directions[i][0];
            int new_y = current.y + directions[i][1];

            if (new_x >= 0 && new_x < data->map_width && new_y >= 0 && new_y < data->map_height &&
                !visited[new_y][new_x] && (data->map[new_y][new_x] == '0' || data->map[new_y][new_x] == 'C' || data->map[new_y][new_x] == 'E')) {
                visited[new_y][new_x] = true;
                queue[rear++] = (t_position){new_x, new_y};
            }
        }
    }

    for (int i = 0; i < data->map_height; i++) {
        free(visited[i]);
    }
    free(visited);
    return false;
}


bool is_map_rectangular(t_data *data)
{
    for (int i = 1; i < data->map_height; i++) {
        if (strlen(data->map[i]) != strlen(data->map[0])) {
            return false;
        }
    }
    return true;
}
int count_collectibles(t_data *data)
{
    int count = 0;

    // Parcourir la carte pour compter les collectibles
    for (int y = 0; y < data->map_height; y++) {
        for (int x = 0; x < data->map_width; x++) {
            if (data->map[y][x] == 'C') {  // Comptage des collectibles
                count++;
            }
        }
    }
    printf("Initial collectible count: %d\n", count);  // Affichage du comptage des collectibles (facultatif)
    return count;
}
