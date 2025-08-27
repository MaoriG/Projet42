/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:28:07 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/27 20:40:21 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_count_line(t_game *game, int fd)
{
	char	*line;
	bool	flag;

	game->map_height = 0;
	game->map_width = 0;
	flag = true;
	while (flag)
	{
		line = get_next_line(fd);
		if (!line)
			flag = false;
		if (flag)
			game->map_height++;
		free(line);
	}
	get_next_line(-42);
}

int	flood_fill_check(char **map, int map_height, int x, int y)
{
	if (y < 0 || y >= map_height || x < 0 || x >= (int)ft_strlen(map[y]))
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] != '0' && map[y][x] != 'N' && map[y][x] != 'S'
		&& map[y][x] != 'E' && map[y][x] != 'W')
		map[y][x] = 'V';
	if (flood_fill_check(map, map_height, x + 1, y))
		return (1);
	if (flood_fill_check(map, map_height, x - 1, y))
		return (1);
	if (flood_fill_check(map, map_height, x, y + 1))
		return (1);
	if (flood_fill_check(map, map_height, x, y - 1))
		return (1);
	return (0);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

void	ft_bzero(void *ptr, unsigned int n)
{
	unsigned char	*p;
	unsigned int	i;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

void	apply_movement(t_player *player, t_game *game)
{
	t_move	ctx;

	if (!(player->key_up || player->key_down || player->key_left
			|| player->key_right))
		return ;
	ctx.player = player;
	ctx.game = game;
	ctx.speed = MOVE_SPEED;
	ctx.cos_a = cos(player->angle);
	ctx.sin_a = sin(player->angle);
	move_player_help(&ctx);
}
