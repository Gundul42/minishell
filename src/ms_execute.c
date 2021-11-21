/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:57:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/21 17:29:01 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**get_argv(t_split *data, char *name)
{
	int		i;
	int		max;
	char	**argv;

	max = 0;
	while (ft_strlen(data->tokens[max]))
		max++;
	max++;
	argv = ft_calloc(max + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(name);
	i = 1;
	while (ft_strlen(data->tokens[i]))
	{
		argv[i] = ft_strdup(data->tokens[i]);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static
void	ms_run_prog(t_list **head, t_split *data)
{
	char	*name;
	int		status;
	pid_t	pid;

	pid = 0;
	status = 0;
	name = NULL;
	name = ms_file_exists(data->tokens[0], ms_getenv(*head, "PATH"), 0);
	if (name)
	{
		pid = fork();
		if (!pid)
			pipe_exec(name, head, data);
	}
	else
		status = ms_print_error(head, data->tokens[0], 127);
	waitpid(pid, &status, 0);
	close_one_pipe(data);
	free(name);
}

static
int	ms_builtin(t_split *data, t_list **head)
{
	int	len;
	int	blt;

	len = ft_strlen(data->tokens[0]);
	blt = chk_builtin(data, len);
	if (blt)
		return (built_exec(data, head, len));
	else if (!blt && len)
		ms_run_prog(head, data);
	return (0);
}

int	ms_execute(t_list **head, t_list **lsthead)
{
	t_split	*content;
	int		err;

	err = 0;
	if (!head || !lsthead)
		return (0);
	if (ft_lstsize(*lsthead) > 1)
		err = err | init_pipes(lsthead);
	while (*lsthead && err >= 0)
	{
		content = (t_split *)((*lsthead)->content);
		err = ms_redirect(head, content);
		if (!err)
			err = err | ms_builtin(content, head);
		err = err | ms_close_redir(head, content);
		ms_delfirst_entry(lsthead);
	}
	return (err);
}
