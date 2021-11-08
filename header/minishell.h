/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:07:32 by graja             #+#    #+#             */
/*   Updated: 2021/11/08 18:54:35 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_split
{
	int		i;
	char	tokens[40][200];
}		t_split;

typedef struct s_env
{
	char	*name;
	char	*value;
}		t_env;

void	check_and_insert_spaces(char **line);
void	ms_input_parser(char *input, t_split *data);
void	ms_builtin_pwd(t_list **head);
void	ms_builtin_echo(t_split *data);
void	ms_builtin_export(t_list **head, t_split *data);
void	ms_builtin_unset(t_list **head, t_split *data);
void	ms_delentry(void *lst);
int		ms_add2list(t_list **ehead, char *str);
int		ms_init_env(t_list **ehead, char **env);
int		ms_insnewlst(t_list **head, char *name, char *val);
int		ms_putenv(t_list **head, char *name, char *val);
int		ms_builtin_cd(t_list **head, t_split *data);
int		ms_builtin_env(t_list **head);
int		ms_execute(t_list **head, t_split *data );
int		ms_getenvnbr(t_list **head);
char	*ms_getprompt(t_list *head);
char	*ms_getenv(t_list *head, char *str);
char	**ms_split(char	*str);
char	*scan_input(char *input);
char	*ms_file_exists(char *name, char *path);
char	**ms_exportenv(t_list **head);
char	**get_argv(t_split *data, char *name);
t_env	**ms_sortenv(t_list **head);

#endif
