/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:13 by mgobert           #+#    #+#             */
/*   Updated: 2025/07/08 19:31:58 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < src_len && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

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
	line = ft_calloc(len, sizeof(char) + 1);
	if (!line)
	{
		free(line);
		perror("Erreur d'allocation mémoire");
		return (NULL);
	}
	else
		ft_strlcpy(line, c, len);
	free(c);
	return (line);
}

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

int	get_map(t_game *game, const char *map_file)
{
	int		file;
	int		map_size;
	char	*line;
	int		i;

	file = open(map_file, O_RDONLY);
	map_size = 0;
	line = NULL;
	if (file < 0)
		return (printf("Erreur d'ouverture du fichier"), 1);
	ft_count_line(game, file);
	close(file);
	file = open(map_file, O_RDONLY);
	game->map = ft_calloc(sizeof(char *), (game->map_height + 1));
	if (!game->map)
		return (close(file), perror("Erreur d'allocation mémoire"), 1);
	i = 0;
	while (i < game->map_height)
	{
		game->map[i] = read_line(file);
		i++;
	}
	return (get_next_line(-42), close(file), 0);
}

int	flood_fill_check(char **map, int x, int y)
{
	if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == '\0')
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



