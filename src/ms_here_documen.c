/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_documen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:56:51 by graja             #+#    #+#             */
/*   Updated: 2021/11/22 17:49:19 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	create_temporary_file(void)
{
	return (open(".tmp_hdocu", O_WRONLY | O_CREAT | O_TRUNC, 0600));
}

static
void	get_and_write_input(t_list **head, t_split *ctt, int tmp_fd)
{
	char	*input;

	/*	signal(SIGINT, interrupt_here_document);*/
	while (head)
	{
		input = readline("> ");
		if (!input)
		{
			close(tmp_fd);
			exit(0);
		}
		if (ft_strncmp(input, ctt->iname, ft_strlen(ctt->iname)))
			ft_putendl_fd(input, tmp_fd);
		else
		{
			close(tmp_fd);
			free(input);
			break ;
		}
		free(input);
	}
	exit(0);
}

static
void	restores_stdin_and_closes()
{
	int		tmp_fd;

	tmp_fd = open(".tmp_hdocu", O_RDONLY);
	unlink(".tmp_hdocu");
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
}

void	here_doc_input(t_list **head, t_split *ctt)
{
	int		tmp_fd;
	int		pipefd_out;
	int		pid;
	int		status;

	tmp_fd = create_temporary_file();
	if (tmp_fd == -1)
		return ;
	pipefd_out = dup(STDOUT_FILENO);
	if (ctt->pipenbr > 1)
		dup2(ctt->pipefd[ctt->pipenbr + 1], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		get_and_write_input(head, ctt, tmp_fd);
	waitpid(pid, &status, 0);
	//that's for when I use cntl+d and stop the << 
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(tmp_fd);
	}
	restores_stdin_and_closes();
	dup2(pipefd_out, STDOUT_FILENO);
	close(pipefd_out);
}

