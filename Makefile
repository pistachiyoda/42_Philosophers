NAME = philo
CC = gcc
CFILES = main.c
CFLAGS = -Wall -Wextra -Werror
OBJ = $(CFILES:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
