/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:49:47 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/27 20:54:01 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* static int	read_params(t_game *game, int fd, char **first_map_line)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		if (is_map_line(line))
		{
			*first_map_line = line;
			return (0);
		}
		if (parse_param(game, line) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

static int	read_map(int fd, char *first_map_line, char ***map_lines,
		int *map_size)
{
	char	*line;

	if (first_map_line)
	{
		if (add_line_to_map(map_lines, first_map_line, map_size) < 0)
		{
			free(first_map_line);
			return (-1);
		}
		free(first_map_line);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		if (add_line_to_map(map_lines, line, map_size) < 0)
		{
			return (free(line), -1);
		}
		free(line);
	}
	return (0);
}

int	read_map_lines(t_game *game, int fd, char ***map_lines, int *map_size)
{
	char *first_map_line = NULL;

	if (read_params(game, fd, &first_map_line) < 0)
		return (-1);
	if (read_map(fd, first_map_line, map_lines, map_size) < 0)
		return (-1);
	return (0);
} */
