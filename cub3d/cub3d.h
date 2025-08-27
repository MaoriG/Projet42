/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:07:30 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/27 20:56:02 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx/mlx.h"
# include "./minilibx/mlx_int.h"
# include "stdbool.h"
# include "string.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1920
# define HEIGHT 1080
# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define CEILING_COLOR 0x87CEEB
# define FLOOR_COLOR 0x228B22

# define PI 3.14159265359

# define MOVE_SPEED 3
# define ANGLE_SPEED 0.03f

# define DEBUG 0

typedef struct s_config
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_color;
	int			ceil_color;
}				t_config;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	char		dir;

	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rotate;
	bool		right_rotate;
}				t_player;

typedef struct s_tex
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_tex;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	char		**map;
	int			map_height;
	int			map_width;
	t_tex		textures[4];
	bool		running;
	t_config	config;

}				t_game;

typedef struct s_ray
{
	float		ray_x;
	float		ray_y;
	float		dir_x;
	float		dir_y;
	int			map_x;
	int			map_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		side_dist_x;
	float		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	float		perp_wall_dist;
	float		hit_x;
	float		hit_y;
}				t_ray;

typedef struct s_wall
{
	float		dist;
	float		height;
	int			start_y;
	int			end;
	int			tex_x;
	int			tex_y;
	float		step;
	float		tex_pos;
	t_tex		*tex;
}				t_wall;

typedef struct s_column
{
	t_player	*player;
	t_game		*game;
	float		hit_x;
	float		hit_y;
	int			i;
	int			side;
	float		ray_angle;
}				t_column;

typedef struct s_square
{
	int			x;
	int			y;
	int			size;
	int			color;
}				t_square;

typedef struct s_point
{
	float		x;
	float		y;
}				t_point;

typedef struct s_move
{
	t_player	*player;
	t_game		*game;
	int			speed;
	float		cos_a;
	float		sin_a;
}				t_move;

int				init_player(t_player *player, t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				get_map(t_game *game, const char *map_file);
char			*ft_strdup(const char *s);
void			*ft_calloc(size_t num, size_t size);
int				flood_fill_check(char **map, int map_height, int x, int y);
char			**copy_map(char **map, int height);
void			clean_map(t_game *game, char **map);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
void			draw_map(t_game *game);
int				draw_loop(t_game *game);
bool			touch(float px, float py, t_game *game);
void			ft_count_line(t_game *game, int fd);
void			draw_square(t_square sq, t_game *game);
void			put_pixel(int x, int y, int color, t_game *game);
void			clear_image(t_game *game);
float			distance(float x, float y);
int				get_tex_pixel(t_tex *tex, int x, int y);
void			draw_ceiling(t_game *game);
float			fixed_dist(t_point p1, t_point p2, t_game *game,
					float ray_angle);
void			render_column(t_column *col);
void			cast_ray(t_player *player, t_game *game, float ray_angle,
					int i);
void			free_textures(t_game *game);
int				exit_game(t_game *game);
void			destroy_game(t_game *game);
void			ft_error(char *error, t_game *game);
int				find_player(t_game *g);
void			set_player(t_player *player, char dir);
int				find_more_player(t_game *game);
void			ft_bzero(void *ptr, unsigned int n);
bool			is_wall(float px, float py, t_game *game);
void			move_player(t_player *player, t_game *game);
void			move_player_help(t_move *ctx);
void			clear_image(t_game *game);
int				init_textures(t_game *game);
void			analyse(t_ray *ray, t_game *game);
void			apply_movement(t_player *player, t_game *game);
char			*ft_strjoin_free(char *s1, char *s2);
void			free_tab(char **tab);
int				parse_cub_file(t_game *game, char *filename);
int				read_map_lines(t_game *game, int fd, char ***map_lines,
					int *map_size);
int				add_line_to_map(char ***map_lines, char *line, int *size);
void			set_map_dimensions(t_game *game);
bool			is_map_line(char *line);
int				parse_param(t_game *game, char *line);
int				parse_color(char *str);
void			normalize_map(t_game *game);
void			print_map(t_game *game);
int				parse_param_help(char **split, t_game *game, char *path,
					int ret);

#endif