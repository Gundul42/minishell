/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipeexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:07:08 by graja             #+#    #+#             */
/*   Updated: 2021/11/30 11:06:51 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* This is for the main process, this one ONLY closes the FDs it
 * does not need. This is very important ! Depending on the position
 * in the iteration of the pipe loop it only closes read, write or both FDs !
 * changing the right way will lead to non working. Race or break condition !
 * HANDS OFF ! */
void	close_one_pipe(t_split *data)
{
	int	in;

	if (data->piped < 1)
		return ;
	in = data->pipenbr * 2;
	if (!data->pipenbr)
		close (data->pipefd[1]);
	else if (data->pipenbr > 0 && data->pipenbr != data->piped)
	{
		close(data->pipefd[in + 1]);
		close(data->pipefd[in - 2]);
	}
	else if (data->pipenbr == data->piped)
	{
		close(data->pipefd[in - 2]);
		free(data->pipefd);
	}
}

/* This is for INSIDE child process, it closes every single fd
 * child process will close as soon as the cmd has finished, so
 * just close all FDs because the process will exit shortly*/
void	close_pipes(t_split *data)
{
	int	in;
	int	i;

	if (data->piped < 1)
		return ;
	in = data->piped * 2 + 1;
	i = 0;
	while (i <= in)
	{
		close(data->pipefd[i]);
		i++;
	}
}

/* open the RIGHT FDs for the pipes, first in the row only needs
 * write access, last one only read access. Any pipe in between
 * needs read access to the last pipe and write access to the
 * next pipe. */
void	pipe_exec(char *name, t_list **head, t_split *data)
{
	int	in;
	int	err;

	err = 0;
	if (data->piped < 1)
		err = execve(name, get_argv(data, name), ms_exportenv(head));
	else
	{
		in = data->pipenbr * 2;
		if (!data->redo && !data->appo && data->pipenbr != data->piped)
			dup2(data->pipefd[in + 1], STDOUT_FILENO);
		if (!data->redi && !data->appi && data->pipenbr > 0)
			dup2(data->pipefd[in - 2], STDIN_FILENO);
		err = execve(name, get_argv(data, name), ms_exportenv(head));
		close_pipes(data);
	}
	if (err)
		exit(errno);
}
