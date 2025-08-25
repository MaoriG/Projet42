/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:05:53 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/25 20:37:33 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_player *player, t_game *game)
{
	char	**mapcopy;
	int		map_x;
	int		map_y;

	if (find_player(game))
		return ;
	map_x = game->player.x / BLOCK;
	map_y = game->player.y / BLOCK;
	if (!(mapcopy = copy_map(game->map, game->map_height)))
		ft_error("Erreur copie de la map", game);
	if (flood_fill_check(mapcopy, map_x, map_y))
	{
		clean_map(game, mapcopy);
		ft_error("Error map", game);
	}
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	clean_map(game, mapcopy);
}

void	move_player(t_player *player)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 3;
	angle_speed = 0.03;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up || player->key_down || player->key_left
		|| player->key_right)
		move_player_help(player, speed, cos_angle, sin_angle);
}

void	move_player_help(t_player *player, int speed, float cos_angle,
		float sin_angle)
{
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
}
