NAME = cub3d

MLX = ./minilibx/libmlx.a
GNL = ./get_next_line/get_next_line.a
INC_DIR = inc/
SRC_DIR = ./src/

SRC = $(SRC_DIR)main.c \
	  $(SRC_DIR)player.c \
	  $(SRC_DIR)map.c \
	  $(SRC_DIR)raycast.c \
	  $(SRC_DIR)utils.c \
	  $(SRC_DIR)utils_help.c \
	  $(SRC_DIR)textures.c \
	  $(SRC_DIR)clean.c \
	  $(SRC_DIR)cast_ray.c \
	  $(SRC_DIR)column.c \
	  $(SRC_DIR)find_player.c \

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I./minilibx -I ./libft
MLX_FLAGS = -L./minilibx -lmlx -lXext -lX11 -lm
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(MLX) $(GNL)
	@echo "🔨 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) $(GNL) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	@echo "💻 Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	$(RM) $(OBJ)

fclean: clean
	@echo "🧼 Cleaning everything..."
	$(RM) $(NAME)

re: fclean all

$(LIBFT):
	make -C ./libft

$(FT_PRINTF):
	make -C ./printf

$(GNL):
	make -C ./get_next_line

$(MLX):
	make -C ./minilibx
