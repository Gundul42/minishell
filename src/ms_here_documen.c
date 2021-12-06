/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_documen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:56:51 by graja             #+#    #+#             */
/*   Updated: 2021/11/26 16:12:21 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	create_temporary_file(void)
{
	return (open(".tmp_hdocu", O_WRONLY | O_CREAT | O_TRUNC, 0600));
}

static
int	expand_here(char *str)
{
	int	found;

	while (*str)
	{
		found = 0;
		while (*str && *str == '$')
		{
			found = 1;
			str++;
		}
		if (found && *str && (ft_isalnum(*str) || *str == '?'))
			return (1);
		if (*str)
			str++;
	}
	return (0);
}

static
void	get_and_write_input(t_list **head, t_split *ctt, int tmp_fd)
{
	char	*input;

	signal(SIGINT, interrupt_here_document);
	while (head)
	{
		input = readline("> ");
		if (!input)
			ms_exit_here(tmp_fd, ctt->iname);
		if (ft_strncmp(input, ctt->iname, ft_strlen(input) + 1))
		{
			while (expand_here(input))
				exp_var(&input, 0, head);
			ft_putendl_fd(input, tmp_fd);
		}
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
void	restores_stdin_and_closes(void)
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
	int		pid;
	int		status;

	tmp_fd = create_temporary_file();
	ctt->fdhere = dup(STDIN_FILENO);
	if (tmp_fd == -1)
		return ;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		get_and_write_input(head, ctt, tmp_fd);
		close(tmp_fd);
	}
	waitpid(pid, &status, 0);
	ms_print_error(head, NULL, 0);
	restores_stdin_and_closes();
	close(tmp_fd);
}
