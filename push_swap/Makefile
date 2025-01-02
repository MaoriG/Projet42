# Nom de l'exécutable
NAME = push_swap

# Répertoires
LIBFT = ./libft/libft.a
FT_PRINTF = ./printf/libftprintf.a  # Chemin vers ta bibliothèque ft_printf
SRC_DIR = srcs/
INC_DIR = inc/

# Fichiers source
SRC = $(SRC_DIR)commands/push.c \
      $(SRC_DIR)commands/rev_rotate.c \
      $(SRC_DIR)commands/rotate.c \
      $(SRC_DIR)algo/algo_utils.c\
      $(SRC_DIR)algo/sort_stacks.c \
      $(SRC_DIR)algo/sort_three.c \
      $(SRC_DIR)commands/swap.c \
      $(SRC_DIR)push_swap/handle_errors.c \
      $(SRC_DIR)push_swap/init_b.c \
      $(SRC_DIR)push_swap/init_a.c \
      $(SRC_DIR)push_swap/push_swap.c \
      $(SRC_DIR)push_swap/split.c \
      $(SRC_DIR)push_swap/stack_init.c \
      $(SRC_DIR)push_swap/stack_utils.c \
      $(SRC_DIR)push_swap/stack_utils2.c

# Fichiers objets correspondants
OBJ = $(SRC:.c=.o)

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
RM = rm -f

# Cible par défaut
all: $(NAME)

# Règle pour créer l'exécutable
$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) -o $(NAME)

# Règle pour compiler les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règles pour nettoyer les fichiers objets et l'exécutable
clean:
	$(RM) $(OBJ)
	make clean -C ./libft
	make clean -C ./printf

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft
	make fclean -C ./printf

re: fclean all

.PHONY: all clean fclean re