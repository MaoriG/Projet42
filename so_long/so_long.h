/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:49:21 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/29 16:49:42 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx/mlx.h"
# include "./minilibx/mlx_int.h"
# include "./printf/ft_printf.h"
# include "stdbool.h"
# include "string.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_found
{
	int		found_wall;
	int		found_empty;
	int		found_collectible;
	int		found_exit;
	int		found_player;
}			t_found;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		img_width;
	int		img_height;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles_left;
	bool	collectibles_collected;
	int		steps;
	int		exit;
	int		collectibles;
	int		player;
}			t_data;

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

void		ft_free_all(t_data *data);
void		free_visited(t_data *data, bool **visited, int y);
int			calculate_new_position(int keysym, t_data *data, int *new_x,
				int *new_y);
int			update_player_position(int new_x, int new_y, t_data *data);
void		help_position_player(t_data *data);
int			handle_keypress(int keysym, t_data *data);
int			on_destroy(t_data *data);
int			init_image(t_data *data, char type);
int			init_window(t_data *data);
void		run_game(t_data *data);
void		print_map(t_data *data);
int			main(int argc, char **argv);
char		*read_line(int fd);
void		ft_count_line(t_data *data, int fd);
int			read_map_file(t_data *data, const char *map_file);
int			initialize_game(t_data *data);
int			init_map(t_data *data, const char *map_file);
int			find_player_and_collectibles(t_data *data);
void		draw_map(t_data *data);
void		help_draw_map(t_data *data, int y, int x);
int			count_collectibles(t_data *data);
void		count_steps(t_data *data);
int			ft_check_format(t_data *data);
int			ft_check_col(t_data *data);
int			ft_count_map_parameters(t_data *data);
void		find_player_position(t_data *data);
void		flood_fill(t_data *data, int x, int y, bool **visited);
void		init_visited(t_data *data, bool **visited, int y);
void		print_visited(t_data *data, bool **visited);
bool		are_elements_accessible(t_data *data, bool **visited, int y, int x);
void		steps_track(t_data *data);
bool		check_accessibility(t_data *data);
int			ft_check_format(t_data *data);

#endif