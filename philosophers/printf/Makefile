CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c ft_print_u.c ft_print_str.c ft_print_ptr.c \
      ft_print_nb.c ft_print_hex.c ft_print_c.c ft_print_hex_up.c
OBJ = $(SRC:.c=.o)
NAME = libftprintf.a
AR = ar rc
RANLIB = ranlib
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	$(RANLIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I. -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re