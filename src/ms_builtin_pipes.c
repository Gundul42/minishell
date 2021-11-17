/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:39:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/16 18:17:10 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_check_and_open(t_split *ptr)
{
	int	in;
	int	out;

	in = ptr->pipenbr * 2;
	out = in + 1;
	if (ptr->piped < 1)
		return (0);
	if (ptr->pipenbr == 0)
	{
		ptr->pcpyout = dup(STDOUT_FILENO);
		dup2(ptr->pipefd[out], STDOUT_FILENO);
	}
	else if (ptr->pipenbr > 0 && ptr->pipenbr < ptr->piped)
	{
		ptr->pcpyout = dup(STDOUT_FILENO);
		dup2(ptr->pipefd[out], STDOUT_FILENO);
		ptr->pcpyin = dup(STDIN_FILENO);
		dup2(ptr->pipefd[in], STDIN_FILENO);
	}
	else if (ptr->pipenbr == ptr->piped - 1)
	{
		ptr->pcpyin = dup(STDIN_FILENO);
		dup2(ptr->pipefd[in], STDIN_FILENO);
	}
	return (0);
}	

int	ms_check_and_close(t_split *ptr)
{
	if (ptr->piped < 1)
		return (0);
	if (ptr->pipenbr == 0)
	{
		dup2(ptr->pcpyout, STDOUT_FILENO);
		close(ptr->pcpyout);
	}
	else if (ptr->pipenbr > 0 && ptr->pipenbr < ptr->piped)
	{
		dup2(ptr->pcpyout, STDOUT_FILENO);
		close(ptr->pcpyout);
		dup2(ptr->pcpyin, STDIN_FILENO);
		close(ptr->pcpyin);
	}
	else if (ptr->pipenbr == ptr->piped - 1)
	{
		dup2(ptr->pcpyin, STDIN_FILENO);
		close(ptr->pcpyin);
	}
	return (0);
}

void	built_exec(t_split *data)
{
	int	in;

	if (data->piped < 1)
		return ;
	else
	{
		in = data->pipenbr * 2;
		ms_debug(data);
		printf("TTL %d,  ACT %d", data->piped, data->pipenbr);
		printf(", FDin %d,", data->pipefd[in - 1]);
		printf("FDout %d\n\n", data->pipefd[in]);
		if (data->pipenbr == 0)
			dup2(data->pipefd[1], STDOUT_FILENO);
		else if (data->pipenbr > 0 && data->pipenbr != data->piped)
		{
			dup2(data->pipefd[in - 2], STDIN_FILENO);
			dup2(data->pipefd[in + 1], STDOUT_FILENO);
		}
		else if (data->pipenbr == data->piped)
			dup2(data->pipefd[in - 2], STDIN_FILENO);
	}
}
