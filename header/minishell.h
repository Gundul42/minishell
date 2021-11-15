/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:07:32 by graja             #+#    #+#             */
/*   Updated: 2021/11/15 16:25:38 by graja            ###   ########.fr       */
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
	char	**tokens;
	char	*iname;
	char	*oname;
	int		redi;
	int		redo;
	int		appi;
	int		appo;
	int		fdout;
	int		fdin;
	int		pcpyin;
	int		pcpyout;
	int		piped;
	int		pipenbr;
	int		*pipefd;
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
void	scan_input(char *input, t_list **head, t_list **lsthead);
void	expand_envvars(char **matrix, t_list **head);
void	ms_populate_cmdlst(char **matrix, t_list **lsthead);
void	ms_init_shell(t_list **head, t_list **lsthead);
void	ms_read_arguments(t_list **lsthead);
void	ms_delfirst_entry(t_list **head);
int		ms_add2list(t_list **ehead, char *str);
int		ms_init_env(t_list **ehead, char **env);
int		ms_insnewlst(t_list **head, char *name, char *val);
int		ms_putenv(t_list **head, char *name, char *val);
int		ms_builtin_cd(t_list **head, t_split *data);
int		ms_builtin_env(t_list **head);
int		ms_execute(t_list **head, t_list **lsthead);
int		ms_getenvnbr(t_list **head);
int		expand_or_not(char **matrix, int i);
int		chk_single(char *str);
int		ms_redirect(t_split *content);
int		ms_close_redir(t_split *ptr);
int		init_pipes(t_list **lsthead);
int		ms_check_and_open(t_split *ptr);
int		ms_check_and_close(t_split *ptr);
char	*ms_getprompt(t_list *head);
char	*ms_getenv(t_list *head, char *str);
char	**ms_split(char	*str);
char	*ms_file_exists(char *name, char *path, int i);
char	**ms_exportenv(t_list **head);
char	**get_argv(t_split *data, char *name);
char	**ms_cut_tokens(char *str, t_list **head);
t_env	**ms_sortenv(t_list **head);

#endif
