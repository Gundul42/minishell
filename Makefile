# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 13:23:33 by graja             #+#    #+#              #
#    Updated: 2021/10/27 17:56:18 by graja            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= Libft
SRC		= src/ms_enviro.c src/main.c src/utils.c src/ms_input_parser.c \
		 src/ms_prompt.c src/ms_builtin_cd.c src/ms_builtin_env.c \
		 src/ms_enviro_hlp.c src/ms_execute.c src/ms_builtin_pwd.c \
		 src/ms_builtin_echo.c src/ms_builtin_export.c \
		 src/ms_builtin_unset.c
CC		= gcc
FLAGS		= -Wall -Wextra -Werror -pthread 
RM		= rm -f

$(NAME)	:	$(SRC) $(LIBFT)
	make -C $(LIBFT)
	$(CC) $(FLAGS) $(SRC) -L$(LIBFT) -lft -lreadline -o $(NAME)

all	: $(NAME)


fclean	: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT)

clean	: 
	make clean -C $(LIBFT)

re	: fclean all
