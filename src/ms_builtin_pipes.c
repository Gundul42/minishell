/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:39:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/20 10:35:19 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	built_exec(t_split *data, t_list **head, int len)
{
	int	err;

	err = 0;
	if (len > 3 && !strncmp(data->tokens[0], "exit", len))
		err = -1;
	else if (len > 1 && !strncmp(data->tokens[0], "cd", len))
		ms_builtin_cd(head, data);
	else if (len > 2 && !strncmp(data->tokens[0], "env", len))
		ms_builtin_env(head);
	else if (len > 2 && !strncmp(data->tokens[0], "pwd", len))
		ms_builtin_pwd(head);
	else if (len > 3 && !strncmp(data->tokens[0], "echo", len))
		ms_builtin_echo(data);
	else if (len > 5 && !strncmp(data->tokens[0], "export", len))
		ms_builtin_export(head, data);
	else if (len > 4 && !strncmp(data->tokens[0], "unset", len))
		ms_builtin_unset(head, data);
	close_one_pipe(data);
	return (err);
}
