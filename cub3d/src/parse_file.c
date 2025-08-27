/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:09:42 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/27 20:55:42 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_cub_file(t_game *game, char *filename)
{
	int		fd;
	char	**map_lines;
	int		map_size;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open %s\n", filename), -1);
	map_lines = NULL;
	map_size = 0;
	if (read_map_lines(game, fd, &map_lines, &map_size) < 0)
		return (-1);
	close(fd);
	if (!map_lines || map_size == 0)
		return (printf("Error\nNo map found\n"), -1);
	game->map = map_lines;
	game->map_height = map_size;
	set_map_dimensions(game);
	normalize_map(game);
	return (0);
}

int	read_map_lines(t_game *game, int fd, char ***map_lines, int *map_size)
{
	char	*line;
	int		in_map;

	in_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n')
		{
			if (!in_map && !is_map_line(line))
			{
				if (parse_param(game, line) < 0)
					return (free(line), -1);
			}
			else
			{
				in_map = 1;
				if (add_line_to_map(map_lines, line, map_size) < 0)
					return (free(line), -1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	add_line_to_map(char ***map_lines, char *line, int *size)
{
	new_map = malloc(sizeof(char *) * (*size + 2));
	i = 0;
	if (!new_map)
	{
		printf("Error: Memory allocation failed\n");
		return (-1);
	}
	while (i < *size)
	{
		new_map[i] = (*map_lines)[i];
		i++;
	}
	new_map[i++] = ft_strdup(line);
	new_map[i] = NULL;
	free(*map_lines);
	*map_lines = new_map;
	(*size)++;
	return (0);
}

void	set_map_dimensions(t_game *game)
{
	int	i;
	int	len;

	game->map_width = 0;
	i = 0;
	while (i < game->map_height)
	{
		len = ft_strlen(game->map[i]);
		if (len > game->map_width)
			game->map_width = len;
		i++;
	}
}

int	parse_param(t_game *game, char *line)
{
	char	**split;
	char	*path;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (printf("Error\nInvalid parameter: %s\n", line), -1);
	path = ft_strtrim(split[1], " \t\n\r");
	if (parse_param_help(split, game, path, ret))
		return (-1);
	free_tab(split);
	if (ret)
		return (-1);
	return (0);
}
