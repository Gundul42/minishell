/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:07:32 by graja             #+#    #+#             */
/*   Updated: 2021/12/04 12:33:30 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
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
	int		err;
	int		redi;
	int		redo;
	int		appi;
	int		appo;
	int		fdout;
	int		fdin;
	int		fdhere;
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

void	ms_c_error(t_list **head, char *s1, char *s2, int nbr);
void	ms_free_env(t_list **head, int flag);
void	ms_exit(t_list **env, t_list **ctt);
void	ms_exit_here(int fd, char *str);
void	interrupt_here_document(int signal);
void	ms_welcome(void);
void	exp_var(char **matrix, int i, t_list **head);
void	here_doc_input(t_list **head, t_split *ctt);
void	define_input_signals(void);
void	ms_del_cmd(void *lst);
void	check_and_insert_spaces(char **line);
void	ms_input_parser(char *input, t_split *data);
void	ms_builtin_pwd(t_list **head);
void	ms_builtin_echo(t_list **head, t_split *data);
void	ms_builtin_export(t_list **head, t_split *data);
void	ms_builtin_unset(t_list **head, t_split *data);
void	ms_delentry(void *lst);
void	scan_input(char *input, t_list **head, t_list **lsthead);
void	expand_envvars(char **matrix, t_list **head);
void	ms_populate_cmdlst(char **matrix, t_list **lsthead);
void	ms_delfirst_entry(t_list **head);
void	pipe_exec(char *name, t_list **head, t_split *data);
void	close_pipes(t_split *data);
void	close_one_pipe(t_split *data);
void	ms_exit_cmd(t_list **head, t_list **ctt, t_split *data);
int		ms_read_arguments(t_list **lsthead, int i, int ttl);
int		ms_check_token_output(t_split *content, int i);
int		ms_check_token_input(t_split *content, int i);
int		built_exec(t_split *data, t_list **head, int len, t_list **ctt);
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
int		ms_redirect(t_list **head, t_split *content);
int		ms_close_redir(t_split *ptr);
int		init_pipes(t_list **lsthead);
int		ms_check_and_open(t_split *ptr);
int		ms_check_and_close(t_split *ptr);
int		chk_builtin(t_split *data, int len);
int		ms_print_error(t_list **head, const char *str, int nbr);
char	*ms_getprompt(t_list *head);
char	*ms_getenv(t_list *head, char *str);
char	**ms_split(char	*str);
char	*ms_file_exists(char *name, char *path, int i);
char	**ms_exportenv(t_list **head);
char	**get_argv(t_split *data, char *name);
char	**ms_cut_tokens(char *str, t_list **head);
t_env	**ms_sortenv(t_list **head);
void	signal_for_blocking_cmd(void);

#endif
