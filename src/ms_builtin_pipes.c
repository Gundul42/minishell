/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:39:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/15 17:25:54 by graja            ###   ########.fr       */
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
