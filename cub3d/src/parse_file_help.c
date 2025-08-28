/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 21:46:40 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/28 21:47:15 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	read_map_lines(t_game *g, int fd, char ***map, int *size)
{
	char	*line;
	int		in_map;

	in_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n')
		{
			if (!in_map)
			{
				if (is_map_line(line))
					in_map = 1;
				else if (parse_param(g, line) < 0)
					return (free(line), drain_gnl_fd(fd), -1);
			}
			if (in_map && process_map_line(map, size, line) < 0)
				return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
