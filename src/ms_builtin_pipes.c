/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:39:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/15 17:00:56 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_check_and_open(t_split *ptr)
{
	if (ptr->piped < 1)
		return (0);
	if (ptr->pipenbr == 0)
	{
		ptr->pcpyout = dup(STDOUT_FILENO);
		dup2(ptr->pipefd[1], STDOUT_FILENO);
		if (ptr->pcpyin == -1)
			return (2);
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
	return (0);
}	
