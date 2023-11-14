NAME = philo

SRC = main.c additional.c additional_extra.c initilization.c threads.c watch_thread.c routine.c

OBJ = $(SRC:.c=.o)

MANPATH = $(addprefix ./src/, $(SRC))

FLAGS = -Wall -Wextra -Werror -O3 -pthread
#FLAGS = -Wall -Wextra -Werror -pthread

HEADER = ./inc/philo.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(MANPATH)

%.o: ./src/%.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re