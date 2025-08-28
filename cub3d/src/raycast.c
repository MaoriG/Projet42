/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:31:39 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/28 21:34:50 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	move_player(player, game);
	clear_image(game);
	draw_ceiling(game);
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

float	fixed_dist(t_point p1, t_point p2, t_game *game, float ray_angle)
{
	float	delta_x;
	float	delta_y;
	float	dist;
	float	angle_diff;

	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
	dist = sqrt(delta_x * delta_x + delta_y * delta_y);
	angle_diff = ray_angle - game->player.angle;
	return (dist * cos(angle_diff));
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = (int *)(game->data + y * game->size_line + x * (game->bpp / 8));
	*dst = color;
}
