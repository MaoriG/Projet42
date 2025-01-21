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
# include "stdbool.h"

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
    int     collectibles_left;
    bool    collectibles_collected;
} t_data;

typedef struct s_position {
    int x;
    int y;
} t_position;

int on_destroy(t_data *data);
void draw_map(t_data *data);
int init_map(t_data *data, const char *map_file);
char **read_map(const char *filename, int map_size);
int get_map_size(const char *filename);
char	*get_next_line(int fd);
int init_image(t_data *data, char type);
int verif_map (t_data *data);
void free_map(t_data *data);
int handle_keypress(int keysym, t_data *data);
bool is_exit_reachable(t_data *data);
void check_and_place_exit(t_data *data);
bool is_map_rectangular(t_data *data);
int count_collectibles(t_data *data);
void collect_item(t_data *data);
#endif