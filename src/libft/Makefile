# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 21:00:06 by nrontey           #+#    #+#              #
#    Updated: 2024/02/21 23:52:08 by nrontey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
CLEAR = clear

# Files
SRC = $(shell find . -name "*.c")
OBJ = $(SRC:.c=.o)

# Color
GREEN	= \033[38;5;76m
RED		= \033[38;5;160m
YELLOW	= \033[38;5;226m
ORANGE	= \033[38;5;202m
PURPLE	= \033[38;5;213m
LBLUE	= \033[38;5;51m
BLUE	= \033[38;5;117m
INDI	= \033[38;5;99m
RESET	= \033[00m

# Compilation
all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)libft compiled! 🫶                                          $(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(LBLUE)Compiling $<...$(RESET)\r"

clean:
	@$(RM) $(OBJ)
	@echo "$(RED)Objects removed 🗑️ $(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)libft removed 🗑️ $(RESET)"

re: fclean all

.PHONY: all clean fclean re
