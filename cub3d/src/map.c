/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:13 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/27 18:30:34 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*read_line(int fd)
{
	char	*line;
	int		i;
	char	*c;
	int		len;

	line = NULL;
	i = 0;
	c = get_next_line(fd);
	if (!c)
		return (NULL);
	len = ft_strlen(c);
	if (c[len - 1] != '\n')
		len++;
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
	{
		free(line);
		printf("Error\nMemory allocation\n");
		return (NULL);
	}
	else
		ft_strlcpy(line, c, len);
	free(c);
	return (line);
}

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
