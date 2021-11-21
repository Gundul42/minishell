/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:57:50 by graja             #+#    #+#             */
/*   Updated: 2021/11/21 16:54:12 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	handle_input(t_split *ptr)
{
	int	fd;

	fd = open(ptr->iname, O_RDONLY, 0644);
	if (fd == -1)
	{
		ms_print_error(ptr->oname, 0);
		return (1);
	}
	ptr->fdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	if (ptr->fdin == -1)
		return (2);
	return (0);
}

static
int	handle_output(t_split *ptr)
{
	int	fd;

	fd = 0;
	if (ptr->redo == 1)
		fd = open(ptr->oname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (ptr->appo == 1)
		fd = open(ptr->oname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ms_print_error(ptr->oname, 0);
		return (1);
	}
	ptr->fdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	if (ptr->fdout == -1)
		return (2);
	return (0);
}

int	ms_close_redir(t_split *ptr)
{
	int	err;

	err = 0;
	if (ptr->fdin > 0)
	{
		err = dup2(ptr->fdin, STDIN_FILENO);
		close(ptr->fdin);
	}
	if (ptr->fdout > 0)
	{
		err = err | dup2(ptr->fdout, STDOUT_FILENO);
		close(ptr->fdout);
	}
	if (err == -1)
		return (3);
	return (0);
}

int	ms_redirect(t_split *content)
{
	int	err;

	err = 0;
	if (content->redi)
		err = handle_input(content);
	if (content->redo || content->appo)
		err = err | handle_output(content);
	return (err);
}
