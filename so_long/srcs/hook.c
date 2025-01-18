/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:10:29 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/18 18:46:11 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int on_keypress(int keysym, t_data *data)
{
    int new_x = data->player_x;
    int new_y = data->player_y;

    // Déplacer le joueur en fonction de la touche pressée
    if (keysym == 65307) {  // Echap
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        exit(0);
    } else if (keysym == 119) {  // 'z' pour haut
        new_y--;
    } else if (keysym == 97) {   // 'q' pour gauche
        new_x--;
    } else if (keysym == 115) {  // 's' pour bas
        new_y++;
    } else if (keysym == 100) {  // 'd' pour droite
        new_x++;
    }

    // Vérifier si le nouveau mouvement est valide (case vide '0')
    if (new_x >= 0 && new_x < data->map_width && new_y >= 0 && new_y < data->map_height) {
        if (data->map[new_y][new_x] == '0') {  // Si la case est libre
            data->map[data->player_y][data->player_x] = '0';  // Effacer l'ancienne position
            data->map[new_y][new_x] = 'P';  // Placer le joueur sur la nouvelle position
            data->player_x = new_x;  // Mettre à jour la position du joueur
            data->player_y = new_y;
        }
    }

    // Redessiner la carte avec le joueur déplacé
    draw_map(data);
    return 0;
}
int on_destroy(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (0);
}