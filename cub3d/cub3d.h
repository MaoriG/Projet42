/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:07:30 by mgobert           #+#    #+#             */
/*   Updated: 2025/07/10 18:41:57 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx/mlx.h"
# include "./minilibx/mlx_int.h"
# include "./get_next_line/get_next_line.h"
# include "stdbool.h"
# include "string.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

# define debug 0

typedef struct s_player
{
    float x;
    float y;
    float angle;
    
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool left_rotate;
    bool right_rotate;
} t_player;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
    t_player player;
    char **map;
    int map_height;
    int map_width;
    
} t_game;

void init_player(t_player *player, t_game *game);
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);
void move_player(t_player *player);
void move_player_help(t_player *player, int speed, float cos_angle, float sin_angle);
int	get_map(t_game *game, const char *map_file);
int	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t num, size_t size);
void ft_error(char *error);
int	find_player(t_game *game);
int	flood_fill_check(char **map, int x, int y);
char **copy_map(char **map, int height);
void clean_map(t_game *game, char **map);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void draw_map(t_game *game);
void draw_line(t_player *player, t_game *game, float start_x, int i);
int draw_loop (t_game *game);
void draw_line_help(t_player *player, t_game *game, float ray_x, float ray_y, int i);
bool touch(float px, float py, t_game *game);
float fixed_dist(float x1, float y1, float x2, float y2, t_game *game);
void	ft_count_line(t_game *game, int fd);
void draw_square(int x, int y, int size, int color, t_game *game);
void put_pixel(int x, int y, int color, t_game *game);
void clear_image(t_game *game);
float distance (float x, float y);

#endif