/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:57:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/04 09:39:46 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**get_argv(t_split *data, char *name)
{
	int	i;
	int	max;
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

	name = ms_file_exists(data->tokens[0], ms_getenv(*head, "PATH"));
	if (name)
	{
		pid = fork();
		if (!pid)
		{
			printf("%d\n", execve(name, get_argv(data, name), ms_exportenv(head)));
		}
		else
		{
			waitpid(pid, &status, 0);
			free(name);
		}
	}
	else
		printf("%s: command not found\n", data->tokens[0]);
}

int	ms_execute(t_list **head, t_split *data )
{
	int	len;

	len = ft_strlen(data->tokens[0]);
	if (!len)
		return (0);
	else if (len > 3 && !strncmp(data->tokens[0], "exit", len))
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
	else
		ms_run_prog(head, data);
	return (0);
}
