/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:10:11 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/24 18:39:18 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int get_map_size(const char *filename)
{
	FILE *file;
	int lines = 0;
	char c;

	file = fopen(filename, "r");
	if (!file) 
	{
		perror("Erreur d'ouverture du fichier");
		return -1;
	}
	while ((c = fgetc(file)) != EOF) 
	{
		if (c == '\n')
			lines++;
	}
	fclose(file);
	return lines;
}
// malloc ma ligne dans le tableau sans \n
char *read_line(int fd)
{
	char *line;
	int i;
	char *c;
	int	len;

	
	line = NULL;
	i = 0;
	c = get_next_line(fd);// on recup la ligne avec \n
	len = ft_strlen(c);
	if (c[len - 1] != '\n')
		len++;
	line = ft_calloc(len, sizeof(char) + 1);// on malloc la ligne sans le \n;
	if (!line)// verfif malloc
		return (free(line), perror("Erreur d'allocation mémoire"), NULL);
	else
		ft_strlcpy(line, c, len);// copie sans \n;
	free(c);
	return line;
}

void	ft_count_line(t_data *data, int fd)
{
	char *line;
	bool flag;
	
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

// malloc la map dans un un tableau de pointeur
int read_map_file(t_data *data, const char *map_file)
{
	int file;
	int map_size;
	char *line;
	int i;

	file = open(map_file, O_RDONLY);
	map_size = 0;
	line = NULL;
	if (file < 0)// fail open
		return (perror("Erreur d'ouverture du fichier"), 1);
	ft_count_line(data, file);// compte la hauteur du futur tableau
	close(file);
	file = open(map_file, O_RDONLY);
	data->map = ft_calloc(sizeof(char *), (data->map_height + 1));// malloc le tableau
	
	if (!data->map)// on verif le malloc
		return (close(file), perror("Erreur d'allocation mémoire"), 1);
	i = 0;
	while (i < data->map_height)// malloc chaque ligne du tableau
	{
		data->map[i] = read_line(file);
		i++;
	}
	get_next_line(-42);
	close(file);
	data->map_width = ft_strlen(data->map[0]);
	return 0;
}
int initialize_game(t_data *data)
{
	int y = 0, x = 0;
	
	// Trouve la position du joueur
	while (y < data->map_height) {
		x = 0;
		while (x < data->map_width) {
			if (data->map[y][x] == 'P') 
			{ 
				data->player_x = x; 
				data->player_y = y; 
				break;
			}
			x++;
		}
		if (x < data->map_width) break; // Trouvé
		y++;
	}
	// Initialiser les autres éléments du jeu comme les collectibles
	data->collectibles_left = count_collectibles(data);
	data->steps = 0;

	return 0;
}

int init_map(t_data *data, const char *map_file)
{
	if (read_map_file(data, map_file))// fais  le tableau
		return (1);
	if (ft_count_map_parameters(data))// verif parametres
		return (1);
	if (!check_accessibility(data))
		return (1);
	if (ft_check_col(data))
			return (1);
	if (initialize_game(data))
		return (1);
	if (find_player_and_collectibles(data))
		return (1);
	return 0;
}
