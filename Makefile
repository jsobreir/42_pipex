LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC = pipex.c parser.c init.c

OBJ = $(SRC:.c=.o)

NAME = pipex

MAKE = make

HEADER = pipex.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -g

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft

%.o: %.c $(HEADER) 
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re