/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:19:21 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/24 23:30:51 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	find_player_and_collectibles(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				return (0);
			}
			x++;
		}
		y++;
	}
	data->collectibles_left = count_collectibles(data);
	return (0);
}

void	draw_map(t_data *data)
{
	int	pixel_x;
	int	pixel_y;
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			help_draw_map(data, y, x);
			pixel_x = x * 100;
			pixel_y = y * 100;
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr,
				pixel_x, pixel_y);
			mlx_destroy_image(data->mlx_ptr, data->img_ptr);
			x++;
		}
		y++;
	}
}

void	help_draw_map(t_data *data, int y, int x)
{
	if (data->map[y][x] == '1')
		init_image(data, '1');
	else if (data->map[y][x] == '0')
		init_image(data, '0');
	else if (data->map[y][x] == 'C')
		init_image(data, 'C');
	else if (data->map[y][x] == 'E')
		init_image(data, 'E');
	else if (data->map[y][x] == 'P')
		init_image(data, 'P');
}

int	count_collectibles(t_data *data)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}
