NAME = minishell

SRC = main.c parse.c signo.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline

DEL = rm -rf

LIBFT_DIR = libft-main
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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
