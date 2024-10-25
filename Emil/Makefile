# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 11:51:28 by temil-da          #+#    #+#              #
#    Updated: 2024/10/25 17:57:04 by temil-da         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

LFLAGS =  -lreadline -lcurses

CC = cc

LIBFT_DIR = includes/libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC = execution/executor.c execution/handle_builtins.c execution/helper_functions.c main.c \
	parsing/parser.c parsing/helper_functions.c \
	lexing/lexer.c lexing/helper_functions.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
fclean:
	rm -f $(OBJ)
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
re: fclean all