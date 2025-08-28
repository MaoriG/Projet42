/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:09:42 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/28 21:47:54 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_cub_file(t_game *game, char *filename)
{
	int		fd;
	char	**map_lines;
	int		map_size;

	fd = open(filename, O_RDONLY);
	map_lines = NULL;
	map_size = 0;
	if (fd < 0)
		return (printf("Error\nCannot open %s\n", filename), -1);
	if (read_map_lines(game, fd, &map_lines, &map_size) < 0)
		return (free(map_lines), -1);
	close(fd);
	if (!map_lines || map_size == 0)
		return (printf("Error\nNo map found\n"), -1);
	game->map = map_lines;
	game->map_height = map_size;
	set_map_dimensions(game);
	normalize_map(game);
	return (0);
}

int	process_map_line(char ***map, int *size, char *line)
{
	if (!is_map_line(line))
	{
		free(line);
		return (-1);
	}
	if (add_line_to_map(map, line, size) < 0)
		return (free(line), -1);
	return (0);
}

int	add_line_to_map(char ***map_lines, char *line, int *size)
{
	char	**new_map;
	int		i;

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
	int		res;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
	{
		printf("Error\nInvalid parameter: %s\n", line);
		free_tab(split);
		return (-1);
	}
	path = ft_strtrim(split[1], " \t\n\r");
	if (!path || path[0] == '\0')
	{
		printf("Error\nInvalid parameter: %s\n", line);
		free(path);
		free_tab(split);
		return (-1);
	}
	res = parse_param_help(split, game, path);
	free_tab(split);
	if (res == 0)
		return (0);
	return (-1);
}
