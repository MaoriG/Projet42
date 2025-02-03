/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:10:11 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/29 16:46:24 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*read_line(int fd)
{
	char	*line;
	int		i;
	char	*c;
	int		len;

	line = NULL;
	i = 0;
	c = get_next_line(fd);
	len = ft_strlen(c);
	if (c[len - 1] != '\n')
		len++;
	line = ft_calloc(len, sizeof(char) + 1);
	if (!line)
		return (free(line), perror("Erreur d'allocation mémoire"), NULL);
	else
		ft_strlcpy(line, c, len);
	free(c);
	return (line);
}

void	ft_count_line(t_data *data, int fd)
{
	char	*line;
	bool	flag;

	data->map_height = 0;
	flag = true;
	while (flag)
	{
		line = get_next_line(fd);
		if (!line)
			flag = false;
		if (flag)
			data->map_height++;
		free(line);
	}
	get_next_line(-42);
}

int	read_map_file(t_data *data, const char *map_file)
{
	int		file;
	int		map_size;
	char	*line;
	int		i;

	file = open(map_file, O_RDONLY);
	map_size = 0;
	line = NULL;
	if (file < 0)
		return (ft_printf("Erreur d'ouverture du fichier"), 1);
	ft_count_line(data, file);
	close(file);
	file = open(map_file, O_RDONLY);
	data->map = ft_calloc(sizeof(char *), (data->map_height + 1));
	if (!data->map)
		return (close(file), perror("Erreur d'allocation mémoire"), 1);
	i = 0;
	while (i < data->map_height)
	{
		data->map[i] = read_line(file);
		i++;
	}
	data->map_width = ft_strlen(data->map[0]);
	return (get_next_line(-42), close(file), 0);
}

int	initialize_game(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				break ;
			}
			x++;
		}
		if (x < data->map_width)
			break ;
		y++;
	}
	data->collectibles_left = count_collectibles(data);
	data->steps = 0;
	return (0);
}

int	init_map(t_data *data, const char *map_file)
{
	if (read_map_file(data, map_file))
		return (ft_free_all(data), 1);
	if (!ft_check_format(data))
		return (ft_free_all(data), 1);
	if (ft_count_map_parameters(data))
		return (ft_free_all(data), 1);
	if (!check_accessibility(data))
		return (ft_free_all(data), 1);
	if (ft_check_col(data))
		return (ft_free_all(data), 1);
	if (initialize_game(data))
		return (ft_free_all(data), 1);
	if (find_player_and_collectibles(data))
		return (ft_free_all(data), 1);
	return (0);
}
