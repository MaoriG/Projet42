/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:28:07 by mgobert           #+#    #+#             */
/*   Updated: 2025/07/10 18:40:24 by mgobert          ###   ########.fr       */
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

int	flood_fill_check(char **map, int x, int y)
{
	if (y < 0 || map[y] == NULL || x < 0 || x >= (int)ft_strlen(map[y]))
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] != '0' && map[y][x] != 'N')
		return (1);
	map[y][x] = 'V';
	if (flood_fill_check(map, x + 1, y))
		return (1);
	if (flood_fill_check(map, x - 1, y))
		return (1);
	if (flood_fill_check(map, x, y + 1))
		return (1);
	if (flood_fill_check(map, x, y - 1))
		return (1);
	return (0);
}