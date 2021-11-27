/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:57:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/27 14:37:45 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**get_argv(t_split *data, char *name)
{
	int		i;
	int		max;
	char	**argv;

	max = 0;
	while (data->tokens[max] != NULL)
		max++;
	max++;
	argv = ft_calloc(max + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(name);
	i = 1;
	while (data->tokens[i] != NULL)
	{
		if (ft_strlen(data->tokens[i]))
			argv[i] = ft_strdup(data->tokens[i]);
		else
			argv[i] = ft_calloc(1, sizeof(char));
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
		status = ms_print_error(head, data->tokens[0], errno);
	waitpid(pid, &status, 0);
	ms_print_error(head, NULL, errno);
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
	signal_for_blocking_cmd();
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
		err = err | ms_close_redir(content);
		ms_delfirst_entry(lsthead);
		if (!err)
			ms_print_error(head, NULL, errno);
	}
	return (err);
}
