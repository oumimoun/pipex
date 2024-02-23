HEADER = pipex.h
CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = pipex
SRC = ./mandatory/pipex.c ./mandatory/ft_split.c ./mandatory/pipex_utils.c ./mandatory/ft_print_error.c ./mandatory/ft_strjoin.c ./mandatory/ft_strncmp.c ./mandatory/ft_strlen.c ./mandatory/ft_free.c
OBJ = $(SRC:.c=.o)

NAME_BONUS = pipex_bonus
SRC_BONUS = ./bonus/pipex_bonus.c \
	./bonus/ft_split.c \
	./bonus/ft_strncmp.c \
	./bonus/pipex_utils_bonus.c\
	./bonus/ft_print_error.c \
	./bonus/ft_free.c \
	./bonus/ft_strlen.c \
	./bonus/ft_strjoin.c \
	./bonus/ft_multiple_pipes.c \
	./bonus/ft_here_doc.c \
	./get_next_line/get_next_line_utils.c \
	./get_next_line/get_next_line.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)

# mandaroty rules

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# bonus relues

bonus: $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) -o $(NAME_BONUS)


# clean rules

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
