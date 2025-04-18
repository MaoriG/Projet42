# Nom de l'exécutable
NAME = so_long

# Répertoires
LIBFT = ./libft/libft.a
FT_PRINTF = ./printf/libftprintf.a
MLX = ./minilibx/libmlx.a
GNL = ./get_next_line/get_next_line.a
SRC_DIR = ./srcs/
INC_DIR = inc/

# Fichiers source
SRC = $(SRC_DIR)main.c \
      $(SRC_DIR)hook.c \
      $(SRC_DIR)map.c \
      $(SRC_DIR)utils.c \
      $(SRC_DIR)map2.c \
      $(SRC_DIR)set.c \
      $(SRC_DIR)free_all.c \
      $(SRC_DIR)utils2.c

# Fichiers objets correspondants
OBJ = $(SRC:.c=.o)

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I./minilibx -I ./libft
MLX_FLAGS = -L./minilibx -lmlx -lXext -lX11
RM = rm -f

# Cible par défaut
all: $(NAME)

# Créer l'exécutable
$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(MLX) $(GNL)
	@echo "🔨 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) $(GNL) $(MLX_FLAGS) -o $(NAME)

# Règle pour compiler les fichiers objets
%.o: %.c
	@echo "💻 Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers objets
clean:
	@echo "🧹 Cleaning object files..."
	$(RM) $(OBJ)

# Supprimer les objets et l'exécutable
fclean: clean
	@echo "🧼 Cleaning everything..."
	$(RM) $(NAME)

# Recompiler tout
re: fclean all

# Règle pour générer la bibliothèque libft
$(LIBFT):
	make -C ./libft

# Règle pour générer la bibliothèque libftprintf
$(FT_PRINTF):
	make -C ./printf

# Règle pour générer la bibliothèque get_next_line
$(GNL):
	make -C ./get_next_line

# Règle pour générer la bibliothèque minilibx
$(MLX):
	make -C ./minilibx
