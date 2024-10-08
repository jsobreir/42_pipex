LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC = pipex.c parser.c utils.c

SRC_BONUS = pipex_bonus.c parser_bonus.c utils_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = pipex

NAME_BONUS = pipex_bonus

MAKE = make

HEADER = pipex.h

HEADER_BONUS = pipex_bonus.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -g

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -Wall -Wextra -Werror $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft

bonus: $(NAME) $(OBJ_BONUS)
	$(CC) -Wall -Wextra -Werror -o $(NAME_BONUS) $(OBJ_BONUS) -L$(LIBFT_DIR) -lft

%.o: %.c $(HEADER) $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re