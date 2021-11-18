/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:57:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/18 09:01:16 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**get_argv(t_split *data, char *name)
{
	int		i;
	int		max;
	char	**argv;

	max = 0;
	while (ft_strlen(data->tokens[max]))
		max++;
	max++;
	argv = ft_calloc(max + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(name);
	i = 1;
	while (ft_strlen(data->tokens[i]))
	{
		argv[i] = ft_strdup(data->tokens[i]);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static
void	ms_run_prog(t_list **head, t_split *data)
{
	char	*name;
	int		status;
	pid_t	pid;

	pid = 0;
	status = 0;
	name = NULL;
	name = ms_file_exists(data->tokens[0], ms_getenv(*head, "PATH"), 0);
	if (name)
	{
		pid = fork();
		if (!pid)
		{
			pipe_exec(name, head, data);
		}
		else
		{
			waitpid(pid, &status, 0);
			free(name);
		}
	}
	else
		printf("%s: command not found\n", data->tokens[0]);
	close_one_pipe(data);
	ms_putenv(head, "?", ft_itoa(status));
}

static
int	ms_builtin(t_split *data, t_list **head)
{
	int	len;
	int	blt;

	len = ft_strlen(data->tokens[0]);
	blt = chk_builtin(data, len);
	if (blt)
		built_exec(data);
/*		ms_check_and_open(data);*/
	if (len > 3 && !strncmp(data->tokens[0], "exit", len))
		return (-1);
	else if (len > 1 && !strncmp(data->tokens[0], "cd", len))
		ms_builtin_cd(head, data);
	else if (len > 2 && !strncmp(data->tokens[0], "env", len))
		ms_builtin_env(head);
	else if (len > 2 && !strncmp(data->tokens[0], "pwd", len))
		ms_builtin_pwd(head);
	else if (len > 3 && !strncmp(data->tokens[0], "echo", len))
		ms_builtin_echo(data);
	else if (len > 5 && !strncmp(data->tokens[0], "export", len))
		ms_builtin_export(head, data);
	else if (len > 4 && !strncmp(data->tokens[0], "unset", len))
		ms_builtin_unset(head, data);
	else if (len)
		ms_run_prog(head, data);
	if (blt)
		close_pipes(data);
		/*ms_check_and_close(data);*/
	return (0);
}

void	ms_debug(t_split *content)
{
	int	i;

	i = 0;
	printf("fd(%d)\n", content->pipenbr);
	printf("%d %d %s\n", content->redi, content->appi, content->iname);
	printf("%d %d %s\n", content->redo, content->appo, content->oname);
	printf("\n");
		while (i <= (content->piped * 2) - 1 )
		{
			printf("fd(%d) = %d\n", i, content->pipefd[i]);
			i++;
		}
		printf("\n");
}

int	ms_execute(t_list **head, t_list **lsthead)
{
	t_split	*content;
	int		err;

	err = 0;
	if (!head || !lsthead)
		return (0);
	if (ft_lstsize(*lsthead) > 1)
		err = err | init_pipes(lsthead);
	while (*lsthead && err >= 0)
	{
		content = (t_split *)((*lsthead)->content);
		err = ms_redirect(content);
		err = err | ms_builtin(content, head);
		err = err | ms_close_redir(content);
		ms_delfirst_entry(lsthead);
	}
	return (err);
}
