NAME = philo

INCLUDES_DIR = .
SRC = ft_atol.c main.c philo_routine.c philo_utils.c utils_routine.c utils.c ft_isdigit.c ft_putstr_fd.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -I$(INCLUDES_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re