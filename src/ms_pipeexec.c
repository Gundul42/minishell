/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipeexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:07:08 by graja             #+#    #+#             */
/*   Updated: 2021/11/18 08:43:12 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	close_one_pipe(t_split *data)
{
	int	in;

	if (data->piped < 1)
		return ;
	in = data->pipenbr * 2;
	if (!data->pipenbr)
	{
		close (data->pipefd[1]);
	}
	else
	{
		close(data->pipefd[in + 1]);
		close(data->pipefd[in - 2]);
	}
}


void	close_pipes(t_split *data)
{
	int	in;

	if (data->piped < 1)
		return ;
	in = data->pipenbr * 2;
	if (!data->pipenbr)
	{
		close (data->pipefd[0]);
		close (data->pipefd[1]);
	}
	else
	{
		close(data->pipefd[in - 2]);
		close(data->pipefd[in + 1]);
	}
}

void	pipe_exec(char *name, t_list **head, t_split *data)
{
	int	in;

	if (data->piped < 1)
		execve(name, get_argv(data, name), ms_exportenv(head));
	else
	{
		in = data->pipenbr * 2;
		/*ms_debug(data);
		printf("TTL %d,  ACT %d", data->piped, data->pipenbr);
		printf(", FDin %d,", data->pipefd[in - 1]);
		printf("FDout %d\n\n", data->pipefd[in]);*/
		if (data->pipenbr != data->piped)
			dup2(data->pipefd[in + 1], STDOUT_FILENO);
		if (data->pipenbr > 0 )
			dup2(data->pipefd[in - 2], STDIN_FILENO);
		execve(name, get_argv(data, name), ms_exportenv(head));
		close_pipes(data);
	}
}
