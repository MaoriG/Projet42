/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:02:36 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/28 20:57:09 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_color(char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (-1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_tab(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error\nWrongcolor\n");
		return (-1);
	}
	return ((r << 16) | (g << 8) | b);
}

int	parse_param_help(char **split, t_game *game, char *path)
{
	if (!ft_strncmp(split[0], "NO", 3))
		return (set_path_once(&game->config.no_path, path, "NO"));
	if (!ft_strncmp(split[0], "SO", 3))
		return (set_path_once(&game->config.so_path, path, "SO"));
	if (!ft_strncmp(split[0], "WE", 3))
		return (set_path_once(&game->config.we_path, path, "WE"));
	if (!ft_strncmp(split[0], "EA", 3))
		return (set_path_once(&game->config.ea_path, path, "EA"));
	if (!ft_strncmp(split[0], "F", 2) || !ft_strncmp(split[0], "C", 2))
		return (parse_param_color(split, game, path));
	printf("Error\nUnknown identifier: %s\n", split[0]);
	free(path);
	return (1);
}

bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

void	normalize_map(t_game *game)
{
	int		y;
	int		len;
	int		i;
	char	*new_line;

	y = 0;
	while (y < game->map_height)
	{
		len = ft_strlen(game->map[y]);
		if (len < game->map_width)
		{
			new_line = malloc(game->map_width + 1);
			if (!new_line)
				exit(1);
			i = -1;
			while (++i < len)
				new_line[i] = game->map[y][i];
			while (i < game->map_width)
				new_line[i++] = ' ';
			new_line[i] = '\0';
			free(game->map[y]);
			game->map[y] = new_line;
		}
		y++;
	}
}

void	analyse(t_ray *ray, t_game *game)
{
	while (ray->map_x >= 0 && ray->map_x < game->map_width && ray->map_y >= 0
		&& ray->map_y < game->map_height)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			break ;
	}
}
