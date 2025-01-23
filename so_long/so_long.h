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
# include "./printf/ft_printf.h"
# include "string.h"
# include "stdbool.h"

typedef struct s_found {
    int found_wall; 
    int found_empty; 
    int found_collectible; 
    int found_exit; 
    int found_player;
} t_found;

typedef struct s_data 
{
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
    int     steps;
    int     exit;
    int     collectibles;
    int     player;
} t_data;

typedef struct s_pos{
    int x;
    int y;
} t_pos;



int on_destroy(t_data *data);
void draw_map(t_data *data);
int init_map(t_data *data, const char *map_file);
int get_map_size(const char *filename);
char	*get_next_line(int fd);
int init_image(t_data *data, char type);
int handle_keypress(int keysym, t_data *data);
int count_collectibles(t_data *data);
char *read_line(FILE *file);
int init_map(t_data *data, const char *map_file);
int load_map_data(t_data *data, const char *map_file);
int find_player_and_collectibles(t_data *data);
int verif_access (t_data *data, int y, int x);
int is_accessible(t_data *data);
void count_steps(t_data *data);
int	ft_check_format(t_data *data);
int	ft_check_col(t_data *data);
int	ft_count_map_parameters(t_data *data);
int ft_verif_map_par(t_data *data);
bool check_accessibility(t_data *data);
#endif