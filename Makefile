LIBFT = libft.a

LIBFT_DIR = ../libft/

SRC = pipex.c parser.c

OBJ = $(SRC:.c=.o)

NAME = pipex.a

MAKE = make

HEADER = pipex.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) (CFLAGS) $(OBJ) -o $(NAME)

%.o: %.o $(HEADER) 
	$(CC) -g $(CFLAGS) -c %.c -o %.o

libft:
	$(MAKE) $(LIBFT_DIR)/$(LIBFT)

clean:
	rm -rf $(OBJ)
	($MAKE) $(LIBFT_DIR)/$(LIBFT) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

