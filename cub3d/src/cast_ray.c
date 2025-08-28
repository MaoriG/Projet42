/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:15:00 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/28 21:35:28 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_ray_help(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
	{
		if (BLOCK / ray->dir_x < 0)
			ray->delta_dist_x = -(BLOCK / ray->dir_x);
		else
			ray->delta_dist_x = BLOCK / ray->dir_x;
	}
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
	{
		if (BLOCK / ray->dir_y < 0)
			ray->delta_dist_y = -(BLOCK / ray->dir_y);
		else
			ray->delta_dist_y = BLOCK / ray->dir_y;
	}
}

static void	init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
	ray->map_x = (int)(ray->ray_x / BLOCK);
	ray->map_y = (int)(ray->ray_y / BLOCK);
	init_ray_help(ray);
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

void	calc_wall_hit(t_ray *ray)
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
	analyse(&ray, game);
	calc_wall_hit(&ray);
	col.player = player;
	col.game = game;
	col.hit_x = ray.hit_x;
	col.hit_y = ray.hit_y;
	col.i = i;
	col.side = ray.side;
	col.ray_angle = ray_angle;
	render_column(&col);
}
