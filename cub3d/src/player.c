/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:05:53 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/26 18:46:13 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_player_help(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	init_player(t_player *player, t_game *game)
{
	char	**mapcopy;
	int		map_x;
	int		map_y;

	if (find_player(game))
		return (1);
	map_x = game->player.x / BLOCK;
	map_y = game->player.y / BLOCK;
	mapcopy = copy_map(game->map, game->map_height);
	if (!(mapcopy))
	{
		printf("Error\ncopy map\n");
		return (1);
	}
	if (flood_fill_check(mapcopy, map_x, map_y))
	{
		clean_map(game, mapcopy);
		printf("Error\nmap not up to standard\n");
		return (1);
	}
	init_player_help(player);
	clean_map(game, mapcopy);
	return (0);
}

static void	apply_rotation(t_player *player)
{
	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	move_player(t_player *player, t_game *game)
{
	apply_rotation(player);
	apply_movement(player, game);
}

bool	is_wall(float px, float py, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(px / BLOCK);
	map_y = (int)(py / BLOCK);
	if (map_y < 0 || map_y >= game->map_height || map_x < 0
		|| map_x >= (int)ft_strlen(game->map[map_y]))
		return (true);
	if (game->map[map_y][map_x] == '1')
		return (true);
	return (false);
}
