/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:13 by mgobert           #+#    #+#             */
/*   Updated: 2025/07/10 18:30:36 by mgobert          ###   ########.fr       */
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
void draw_map(t_game *game)
{
    char **map;
    int color;
    int y;
    int x;
    
    color = 0x0000FF;
    map = game->map;
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
            x++;
        }
        y++;
    }
}