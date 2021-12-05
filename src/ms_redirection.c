/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:57:50 by graja             #+#    #+#             */
/*   Updated: 2021/12/05 11:11:49 by dmylonas         ###   ########.fr       */
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
		ms_print_error_for_glob(ptr->iname, -1);
		return (1);
	}
	ptr->fdin = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		ms_print_error_for_glob("dup2", -1);
	if (ptr->fdin == -1)
	{
		ms_print_error_for_glob("dup", -1);
		return (2);
	}
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
		ms_print_error_for_glob(ptr->oname, -1);
		return (1);
	}
	ptr->fdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ms_print_error_for_glob("dup2", -1);
	if (ptr->fdout == -1)
	{
		ms_print_error_for_glob("dup", -1);
		return (2);
	}
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
	if (ptr->fdhere > 0)
	{
		err = err | dup2(ptr->fdhere, STDIN_FILENO);
		close(ptr->fdhere);
	}
	return (err);
}

int	ms_redirect(t_list **head, t_split *content)
{
	int	err;

	err = 0;
	if (content->redi)
		err = handle_input(content);
	if (!err && content->appi)
		here_doc_input(head, content);
	if (!err && (content->redo || content->appo))
		err = err | handle_output(content);
	return (err);
}
