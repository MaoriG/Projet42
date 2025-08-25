/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:37:58 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/25 21:09:53 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player(t_player *player, int map_x, int map_y, char dir)
{
	// Position du joueur au centre du bloc
	player->x = map_x * BLOCK + BLOCK / 2;
	player->y = map_y * BLOCK + BLOCK / 2;

	// Angle selon la lettre
	if (dir == 'N')
		player->angle = 3 * PI / 2; // vers le haut
	else if (dir == 'S')
		player->angle = PI / 2;     // vers le bas
	else if (dir == 'E')
		player->angle = 0;          // vers la droite
	else if (dir == 'W')
		player->angle = PI;         // vers la gauche
}

int	find_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
    while (game->map[0][game->map_width])
		game->map_width++;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'N')
			{
				game->player.x = x * BLOCK;
				game->player.y = y * BLOCK;
                game->map[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
    printf("player not found");
	return (1);
}
