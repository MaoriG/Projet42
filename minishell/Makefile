# Project name
NAME    := minishell

# Compiler and linker
CC      := gcc -g
LD      := gcc -g

# Compilation and linking flags
CFLAGS  := -Wall -Wextra -Werror -I. #-fsanitize=address
LDFLAGS := -lreadline -lhistory #-fsanitize=address

# Source files
SRCS    := main.c\
			src/builtin/cd.c \
			src/builtin/echo.c \
			src/builtin/env.c \
			src/builtin/exit_piped.c \
			src/builtin/exit.c \
			src/builtin/export.c \
			src/builtin/pwd.c \
			src/cmd/free.c \
			src/cmd/search.c \
			src/exec/builtin.c \
			src/exec/exec.c \
			src/exec/multiple_help.c \
			src/exec/multiple.c \
			src/exec/redir_pipe.c \
			src/exec/redir.c \
			src/exec/single.c \
			src/parser/count_segments.c \
			src/parser/free.c \
			src/parser/ft_split.c \
			src/parser/init.c \
			src/parser/parsing_help.c \
			src/parser/parsing_help2.c \
			src/parser/parsing_pipe.c \
			src/parser/set_redir.c \
			src/parser/tokens_help.c \
			src/parser/tokens_help2.c \
			src/parser/tokens.c \
			src/parser/utils.c \
			src/parser/utilshelp.c \
			src/path/assemble.c \
			src/str/array.c \
			src/str/ft_itoa.c \
			src/str/input_help.c \
			src/str/input_heredoc.c \
			src/str/input.c \
			src/str/is_space.c \
			src/str/str_helps.c \
			src/str/str.c \
			src/str/ft_check_quote.c \
			src/str/strcount.c \
			src/utils/atoi.c \
			src/utils/ctx.c \
			src/utils/env.c \
			src/utils/error.c \
			src/utils/heredoc.c \
			src/utils/init.c \
			src/utils/prompt.c \
			src/utils/set.c \
			src/utils/sig.c \
			src/utils/utils1.c \

# Object files
OBJS    := $(SRCS:.c=.o)

# Default target
all: $(NAME)

# Linking
$(NAME): $(OBJS)
	@echo "Linking $@ ..."
	@$(LD) -o $@ $^ $(LDFLAGS)

# Compilation
%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "Removing object files"
	@rm -f $(OBJS)

# Clean everything
fclean: clean
	@echo "Removing executable $(NAME)"
	@rm -f $(NAME)

# Rebuild all
re: fclean all

# Debug target using Valgrind
debug: $(NAME)
	@echo "Running Valgrind on $(NAME)"
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=readline.sup ./$(NAME)

# Declare phony targets
.PHONY: all clean fclean re debug
