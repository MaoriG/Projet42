# Nom de l'exécutable
NAME = philosophers

# Répertoires
LIBFT = ./libft/libft.a
FT_PRINTF = ./printf/libftprintf.a
SRC_DIR = ./srcs/

# Fichiers source
SRC = $(SRC_DIR)main.c \
$(SRC_DIR)utils.c \
$(SRC_DIR)parsing.c \
$(SRC_DIR)dinner.c \
$(SRC_DIR)getters_setters.c \
$(SRC_DIR)init.c \
$(SRC_DIR)safe_function.c \
$(SRC_DIR)synchro.c \
$(SRC_DIR)write.c \
# Fichiers objets correspondants
OBJ = $(SRC:.c=.o)

# Compilateur et flags
CC = cc
MLX_FLAGS = -L./minilibx -lmlx -lXext -lX11
RM = rm -f

# Cible par défaut
all: $(NAME)

# Créer l'exécutable
$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF)
	@echo "🔨 Linking $(NAME)..."
	$(CC) $(OBJ) $(LIBFT) $(FT_PRINTF) -o $(NAME)

# Règle pour compiler les fichiers objets
%.o: %.c
	@echo "💻 Compiling $<"
	$(CC) -c $< -o $@

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

