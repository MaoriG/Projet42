/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:37:58 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/26 20:43:35 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player(t_player *player, char dir)
{
	if (dir == 'N')
		player->angle = 3 * PI / 2;
	else if (dir == 'S')
		player->angle = PI / 2;
	else if (dir == 'E')
		player->angle = 0;
	else if (dir == 'W')
		player->angle = PI;
}

static int	find_player_help(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'W'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'S')
			{
				game->player.x = x * BLOCK;
				game->player.y = y * BLOCK;
				game->player.dir = game->map[y][x];
				game->map[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	find_more_player(t_game *game)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'W'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'S')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	max_map_width(t_game *game)
{
	int	y;
	int	max;
	int	base;

	y = 0;
	max = 0;
	while (game->map[y])
	{
		base = ft_strlen(game->map[y]);
		if (base > max)
			max = ft_strlen(game->map[y]);
		y++;
	}
	return (max);
}

int	find_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	game->map_width = max_map_width(game);
	if (find_player_help(game))
	{
		printf("Player not found\n");
		return (1);
	}
	if (find_more_player(game))
	{
		printf("More than one player found\n");
		return (1);
	}
	set_player(&game->player, game->player.dir);
	return (0);
}
