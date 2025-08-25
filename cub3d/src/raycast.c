/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:31:39 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/25 20:33:51 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_debug(t_game *game, t_player *player)
{
	if (debug)
	{
		draw_square(player->x, player->y, 10, 0x00FF00, game);
		draw_map(game);
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	if (!game->running || !game->win || !game->img)
		return (0);
	player = &game->player;
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	move_player(player);
	clear_image(game);
	draw_floor_ceiling(game);
	draw_debug(game, player);
	i = -1;
	while (++i < WIDTH)
	{
		cast_ray(player, game, start_x, i);
		start_x += fraction;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (y < 0 || y >= game->map_height || x < 0 || x >= ft_strlen(game->map[y]))
		return (true);
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game,
		float ray_angle)
{
	float	delta_x;
	float	delta_y;
	float	dist;
	float	angle_diff;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	dist = sqrt(delta_x * delta_x + delta_y * delta_y);
	angle_diff = ray_angle - game->player.angle;
	return (dist * cos(angle_diff));
}
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}
