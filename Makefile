# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 10:30:54 by tpipi             #+#    #+#              #
#    Updated: 2024/06/13 21:15:44 by tpipi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = 	$(addprefix	utils/, struct_utils.c free_utils.c sig_utils.c) \
		$(addprefix	env_utils/, ft_getenv.c ft_putenv.c ft_putenv_utils.c env_struct_utils.c env_update.c) \
		$(addprefix built-in/, ft_echo.c ft_env.c ft_exit.c ft_cd.c ft_pwd.c ft_export.c ft_export_utils.c ft_unset.c) \
		$(addprefix parsing/, args_utils.c cmdlst_utils.c error.c get_type.c len_utils.c outlst_utils.c redirect.c replace.c utils.c check.c env_var.c free.c index_of.c parsing.c str_utils.c parse_buffer.c check_heredoc.c parsing_utils.c unquote_strtok.c) \
		$(addprefix exec/, filename_utils.c filename_getter.c env_char_utils.c exec.c command_exec.c command_exec_utils.c pipes_utils.c ) \
		$(addprefix redirect/, here_doc.c here_doc_utils.c stdin_redirect.c stdout_redirect.c redirect_utils.c) \
		$(addprefix main/, main.c readline_addon.c tasks_management.c)

SRC := $(addprefix src/, $(SRC))
OBJ = $(SRC:.c=.o)

LIBFT = src/libft/libft.a
LIBFT_DIR = src/libft

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJ) $(LIBFT)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re