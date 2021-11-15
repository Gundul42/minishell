# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 13:23:33 by graja             #+#    #+#              #
#    Updated: 2021/11/15 10:27:35 by graja            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= Libft
SRC		= src/ms_enviro.c src/main.c src/ms_prompt.c \
		 src/ms_builtin_cd.c src/ms_builtin_env.c \
		 src/ms_enviro_hlp.c src/ms_execute.c src/ms_builtin_pwd.c \
		 src/ms_builtin_echo.c src/ms_builtin_export.c \
		 src/ms_builtin_unset.c src/ms_files.c src/ms_sortenv.c \
		 src/token_check_and_insert_spaces.c src/scanner.c \
		 src/ms_cutter.c src/ms_expansion.c src/ms_populatelst.c \
		 src/ms_read_arguments.c src/ms_delfirst_entry.c \
		 src/ms_redirection.c
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
