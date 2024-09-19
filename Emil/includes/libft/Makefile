# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 15:19:00 by temil-da          #+#    #+#              #
#    Updated: 2024/04/14 19:24:49 by temil-da         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = cc

SRC = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c

PRINTF_SRC = free_my.c print_my.c ft_putstr.c ft_putchar.c ft_toupper_printf.c ft_printf.c ft_check_it_out.c ft_itoa_u.c ft_itoa_ptr.c ft_itoa_printf.c ft_itoa_hex.c

GET_NEXT_LINE_SRC = get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS:.c=.o)
PRINTF_OBJ = $(PRINTF_SRC:.c=.o)
GNL_OBJ = $(GET_NEXT_LINE_SRC:.c=.o)

HEADER = libft.h

RED = \033[0;31m
NC = \033[0m
GREEN = \033[0;32m
YELLOW = \033[1;33m

.PHONY: all clean fclean re compile_msg bonus

all : compile_msg $(NAME)

compile_msg:
	@echo "$(YELLOW)Compiling source files...$(NC)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)
	@echo "$(YELLOW)Creating $(NAME) library...$(NC)"
	@ar rsc $@ $^
	@ranlib $@
	@echo "$(GREEN)Done.$(NC)"

clean:
	@$(if $(wildcard $(OBJ) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)), \
        echo "$(YELLOW)Cleaning object files...$(NC)" && rm -f $(OBJ) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ) && echo "$(GREEN)Done.$(NC)", \
        echo "$(RED)No object files to clean!$(NC)")

fclean: clean 
	@$(if $(wildcard $(NAME)), \
        echo "$(YELLOW)Removing $(NAME) library...$(NC)" && rm -f $(NAME) && echo "$(GREEN)Done.$(NC)", \
        echo "$(RED)$(NAME) library non existent!$(NC)")

re: fclean all

bonus: $(BONUS_OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
