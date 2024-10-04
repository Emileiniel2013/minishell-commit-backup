NAME	=	Minishell

CC	=	cc

CFLAGS	=	-Wall -Werror -Wextra -g

LIBFTFDIR	=	include/libft

INCLUDE	=	-L ./include/libft -lft

SRC    := $(shell find ./src -iname "*.c")


OBJ	=	$(SRC:.c=.o)

all: $(NAME)
$(NAME):	$(OBJ)
	@make -sC $(LIBFTFDIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDE) -lreadline -g

clean:
	@rm -f $(OBJ)
	@cd $(LIBFTFDIR) && $(MAKE) clean

fclean:
	$(MAKE) clean
	@rm -f $(NAME)
	@cd $(LIBFTFDIR) && $(MAKE) fclean

re: fclean all

.PHONY: all, clean, fclean, re