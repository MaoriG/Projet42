/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:15:00 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/25 19:31:44 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
	ray->map_x = (int)(ray->ray_x / BLOCK);
	ray->map_y = (int)(ray->ray_y / BLOCK);
	ray->delta_dist_x = (ray->dir_x == 0) ? 1e30 : fabs(BLOCK / ray->dir_x);
	ray->delta_dist_y = (ray->dir_y == 0) ? 1e30 : fabs(BLOCK / ray->dir_y);
	ray->side = -1;
}

static void	set_ray_steps(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->ray_x - ray->map_x * BLOCK) / BLOCK
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((ray->map_x + 1) * BLOCK - ray->ray_x) / BLOCK
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->ray_y - ray->map_y * BLOCK) / BLOCK
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((ray->map_y + 1) * BLOCK - ray->ray_y) / BLOCK
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_game *game)
{
	while (ray->map_x >= 0 && ray->map_x < game->map_width && ray->map_y >= 0
		&& ray->map_y < game->map_height)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			break ;
	}
}

static void	calc_wall_hit(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->ray_x / BLOCK + (1
					- ray->step_x) / 2) * BLOCK / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->ray_y / BLOCK + (1
					- ray->step_y) / 2) * BLOCK / ray->dir_y;
	ray->hit_x = ray->ray_x + ray->dir_x * ray->perp_wall_dist;
	ray->hit_y = ray->ray_y + ray->dir_y * ray->perp_wall_dist;
}

void	cast_ray(t_player *player, t_game *game, float ray_angle, int i)
{
	t_ray		ray;
	t_column	col;

	init_ray(&ray, player, ray_angle);
	set_ray_steps(&ray);
	perform_dda(&ray, game);
	calc_wall_hit(&ray);
	if (!debug)
	{
		col.player = player;
		col.game = game;
		col.hit_x = ray.hit_x;
		col.hit_y = ray.hit_y;
		col.i = i;
		col.side = ray.side;
		col.ray_angle = ray_angle;
		render_column(&col);
	}
	else
		put_pixel((int)ray.hit_x, (int)ray.hit_y, 0xFF0000, game);
}
