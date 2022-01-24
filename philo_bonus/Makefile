NAME = philo_bonus
CC = gcc
CFILES = ./src/atoi.c ./src/parse_args.c ./src/philo_bonus.c ./src/utils.c
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
