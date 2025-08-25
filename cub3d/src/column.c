/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:17:29 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/25 19:32:10 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_wall(t_wall *wall, t_column *col)
{
	float	plane_dist;

	wall->dist = fixed_dist(col->player->x, col->player->y, col->hit_x,
			col->hit_y, col->game, col->ray_angle);
	plane_dist = (WIDTH / 2.0f) / tan(PI / 6.0f);
	wall->height = (BLOCK * plane_dist) / wall->dist;
	wall->start_y = (HEIGHT - wall->height) / 2;
	if (wall->start_y < 0)
		wall->start_y = 0;
	wall->end = wall->start_y + wall->height;
	if (wall->end >= HEIGHT)
		wall->end = HEIGHT - 1;
}

static void	select_texture(t_wall *wall, t_column *col)
{
	float	wall_pos;

	if (col->side == 0)
	{
		wall->tex = (col->hit_x > col->player->x) ? &col->game->textures[2] : &col->game->textures[3];
		wall_pos = fmod(col->hit_y, BLOCK);
		wall->tex_x = (int)((wall_pos / BLOCK) * wall->tex->width);
	}
	else
	{
		wall->tex = (col->hit_y > col->player->y) ? &col->game->textures[1] : &col->game->textures[0];
		wall_pos = fmod(col->hit_x, BLOCK);
		wall->tex_x = (int)((wall_pos / BLOCK) * wall->tex->width);
	}
}

static void	draw_wall_column(t_wall *wall, t_column *col)
{
	int	color;

	wall->step = (float)wall->tex->height / wall->height;
	wall->tex_pos = (wall->start_y - (HEIGHT - wall->height) / 2) * wall->step;
	while (wall->start_y < wall->end)
	{
		wall->tex_y = (int)wall->tex_pos;
		wall->tex_pos += wall->step;
		if (wall->tex_y >= 0 && wall->tex_y < wall->tex->height)
		{
			color = get_tex_pixel(wall->tex, wall->tex_x, wall->tex_y);
			if (col->side == 1)
				color = (color >> 1) & 0x7F7F7F;
			put_pixel(col->i, wall->start_y, color, col->game);
		}
		wall->start_y++;
	}
}

void	render_column(t_column *col)
{
	t_wall	wall;

	init_wall(&wall, col);
	select_texture(&wall, col);
	draw_wall_column(&wall, col);
}
