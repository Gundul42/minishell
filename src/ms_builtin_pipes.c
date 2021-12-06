/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:39:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/29 17:37:00 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	fork_or_not(t_split *data, int len)
{
	if (!data->piped)
		return (0);
	if (len > 2 && !strncmp(data->tokens[0], "env", len))
		return (1);
	else if (len > 2 && !strncmp(data->tokens[0], "pwd", len))
		return (1);
	else if (len > 3 && !strncmp(data->tokens[0], "echo", len))
		return (1);
	else if (len > 5 && !strncmp(data->tokens[0], "export", len))
	{
		if (ft_strlen(data->tokens[1]))
			return (0);
		else
			return (1);
	}
	return (0);
}

static
void	built_pipe(t_split *data)
{
	int	in;
	{
		data->pcpyin = dup(STDIN_FILENO);
		data->pcpyout = dup(STDOUT_FILENO);
		in = data->pipenbr * 2;
		if (data->pipenbr != data->piped)
			dup2(data->pipefd[in + 1], STDOUT_FILENO);
		if (data->pipenbr > 0)
			dup2(data->pipefd[in - 2], STDIN_FILENO);
	}
}

static
void	destroy_pipe(t_split *data)
{
	{
		dup2(data->pcpyin, STDIN_FILENO);
		dup2(data->pcpyout, STDOUT_FILENO);
		close(data->pcpyin);
		close(data->pcpyout);
	}
}

static
int	run_builtin(t_split *data, t_list **head, int len, t_list **ctt)
{
	if (len > 3 && !data->piped && !strncmp(data->tokens[0], "exit", len))
		ms_exit_cmd(head, ctt, data);
	else if (len > 1 && !strncmp(data->tokens[0], "cd", len))
		ms_builtin_cd(head, data);
	else if (len > 2 && !strncmp(data->tokens[0], "env", len))
		ms_builtin_env(head);
	else if (len > 2 && !strncmp(data->tokens[0], "pwd", len))
		ms_builtin_pwd(head);
	else if (len > 3 && !strncmp(data->tokens[0], "echo", len))
		ms_builtin_echo(head, data);
	else if (len > 5 && !strncmp(data->tokens[0], "export", len))
		ms_builtin_export(head, data);
	else if (len > 4 && !strncmp(data->tokens[0], "unset", len))
		ms_builtin_unset(head, data);
	return (0);
}

int	built_exec(t_split *data, t_list **head, int len, t_list **lsthead)
{
	int		err;

	err = 0;
	if (!fork_or_not(data, len))
		err = run_builtin(data, head, len, lsthead);
	else
	{
		built_pipe(data);
		err = run_builtin(data, head, len, lsthead);
		destroy_pipe(data);
	}
	close_one_pipe(data);
	return (err);
}
