# Nom de l'exécutable
NAME = so_long

# Répertoires
LIBFT = ./libft/libft.a
FT_PRINTF = ./printf/libftprintf.a
MLX = ./minilibx/libmlx.a
GNL = ./get_next_line/get_next_line.a  # Bibliothèque statique de get_next_line
SRC_DIR = ./srcs/
INC_DIR = inc/

# Fichiers source
SRC = $(SRC_DIR)main.c \
      $(SRC_DIR)hook.c \
      $(SRC_DIR)map.c \
	  $(SRC_DIR)utils.c \
	  $(SRC_DIR)map2.c \
	  $(SRC_DIR)set.c \

# Fichiers objets correspondants
OBJ = $(SRC:.c=.o)

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I./minilibx
MLX_FLAGS = -L./minilibx -lmlx -lXext -lX11
RM = rm -f

# Cible par défaut
all: $(NAME)

# Règle pour créer l'exécutable
$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(MLX) $(GNL)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) $(GNL) $(MLX_FLAGS) -o $(NAME)

# Règle pour compiler les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règles pour nettoyer les fichiers objets et l'exécutable
clean:
	$(RM) $(OBJ)
	make clean -C ./libft
	make clean -C ./printf
	make clean -C ./get_next_line
	make clean -C ./minilibx

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft
	make fclean -C ./printf
	make fclean -C ./get_next_line
	make clean -C ./minilibx

re: fclean all