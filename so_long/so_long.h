# ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "./minilibx/mlx.h"
# include "./minilibx/mlx_int.h"
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "string.h"

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
	void 	*img_ptr;
    int     img_width;
    int     img_height;
    char    **map;
    int     map_width;
    int     map_height;
	int		player_x;
	int		player_y;
} t_data;

int on_destroy(t_data *data);
int on_keypress(int keysym, t_data *data);
void draw_map(t_data *data);
int init_map(t_data *data, const char *map_file);
char **read_map(const char *filename, int map_size);
int get_map_size(const char *filename);
char	*get_next_line(int fd);
int init_image(t_data *data, char type);
void manage_init (t_data *data, char c);
int verif_map (t_data *data);
void set_content(t_data *data);
void free_map(t_data *data);
#endif