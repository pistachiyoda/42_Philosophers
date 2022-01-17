NAME = philo
CC = gcc
CFILES = ./src/main.c ./src/parse_args.c ./src/atoi.c ./src/start_philos.c ./src/simulation.c ./src/error_handling.c\
		./src/init_philos.c ./src/utils.c ./src/monitor.c\
		./src/handle_folk.c ./src/handle_sleep.c ./src/handle_think.c
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
