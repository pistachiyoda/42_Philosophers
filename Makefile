NAME = philo
CC = gcc
CFILES = ./src/main.c ./src/parse_args.c ./src/atoi.c ./src/start_philos.c ./src/philo.c ./src/error_handling.c
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
