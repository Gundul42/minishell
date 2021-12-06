# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 13:23:33 by graja             #+#    #+#              #
#    Updated: 2021/12/04 12:33:45 by dmylonas         ###   ########.fr        #
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
		 src/ms_redirection.c src/ms_pipes.c src/ms_builtin_pipes.c \
		 src/ms_check_builtin.c src/ms_pipeexec.c src/main_signals.c \
		 src/ms_errors.c src/ms_here_documen.c src/welcome.c \
		 src/ms_exiter.c src/ms_checktoken_input.c \
		 src/ms_checktoken_output.c \
		 src/ms_exit_here.c src/main_signals_extra.c 
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
