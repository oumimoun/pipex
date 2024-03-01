HEADER = pipex.h
CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = pipex
SRC = ./mandatory/pipex.c \
	./mandatory/ft_split.c \
	./mandatory/pipex_utils.c \
	./mandatory/ft_print_error.c \
	./mandatory/ft_strjoin.c \
	./mandatory/ft_strncmp.c \
	./mandatory/ft_strlen.c \
	./mandatory/ft_free.c

OBJ = $(SRC:.c=.o)

NAME_BONUS = pipex_bonus

SRC_BONUS = ./pipex_bonus_folder/pipex_bonus.c \
	./pipex_bonus_folder/ft_split_bonus.c \
	./pipex_bonus_folder/ft_strncmp_bonus.c \
	./pipex_bonus_folder/pipex_utils_bonus.c\
	./pipex_bonus_folder/ft_print_error_bonus.c \
	./pipex_bonus_folder/ft_free_bonus.c \
	./pipex_bonus_folder/ft_strlen_bonus.c \
	./pipex_bonus_folder/ft_strjoin_bonus.c \
	./pipex_bonus_folder/ft_itoa_bonus.c \
	./pipex_bonus_folder/ft_multiple_pipes_bonus.c \
	./pipex_bonus_folder/ft_here_doc_bonus.c \
	./get_next_line/get_next_line_utils_bonus.c \
	./get_next_line/get_next_line_bonus.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) -o $(NAME_BONUS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus