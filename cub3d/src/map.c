/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:13 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/28 20:57:21 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_map(t_game *game)
{
	char		**map;
	int			y;
	int			x;
	t_square	sq;

	map = game->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				sq.x = x * BLOCK;
				sq.y = y * BLOCK;
				sq.size = BLOCK;
				sq.color = 0x0000FF;
				draw_square(sq, game);
			}
			x++;
		}
		y++;
	}
}

char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	i = 0;
	copy = ft_calloc(sizeof(char *), height + 1);
	if (!copy)
		return (NULL);
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

void	draw_square(t_square sq, t_game *game)
{
	int	i;

	i = 0;
	while (i < sq.size)
	{
		put_pixel(sq.x + i, sq.y, sq.color, game);
		put_pixel(sq.x, sq.y + i, sq.color, game);
		put_pixel(sq.x + sq.size, sq.y + i, sq.color, game);
		put_pixel(sq.x + i, sq.y + sq.size, sq.color, game);
		i++;
	}
}

int	parse_param_color(char **split, t_game *game, char *path)
{
	int	color;

	color = parse_color(path);
	if (color < 0)
	{
		free(path);
		return (1);
	}
	if (!ft_strncmp(split[0], "F", 2))
	{
		game->config.floor_color = color;
		free(path);
		return (0);
	}
	if (!ft_strncmp(split[0], "C", 2))
	{
		game->config.ceil_color = color;
		free(path);
		return (0);
	}
	printf("Error\nUnknown identifier: %s\n", split[0]);
	free(path);
	return (1);
}

int	set_path_once(char **dst, char *path, const char *id)
{
	if (*dst)
	{
		printf("Error\nDuplicate identifier: %s\n", id);
		free(path);
		return (1);
	}
	*dst = path;
	return (0);
}
