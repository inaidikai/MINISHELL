NAME = minishell

SRC = prompt.c prepare_variables.c prepare_shell.c parsing.c init_var.c in_outfiles.c here_doc.c \
matrx.c main.c errno.c lexer.c ft_spliter.c  ex_split.c  fillnode.c  \
fillnodeutils.c cmd_cd.c builtins.c cmd_export.c cmd_exit.c exec.c signals.c \
process.c get_next_line.c 

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 

DEL = rm -rf

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# If using Homebrew on macOS for Readline
READLINE_DIR = -L/opt/vagrant/embedded/lib
INCLUDES = -I$(READLINE_DIR)/include/readline/readline.h
LDFLAGS = -lreadline -lhistory

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(READLINE_DIR) $(INCLUDES) $(OBJ) $(LIBFT) -o $@ $(LDFLAGS)
	

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(DEL) $(OBJ) 

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(DEL) $(NAME)

re: fclean all

.PHONY: all clean fclean re
