/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:57:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/02 13:38:31 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_execute(t_list **head, t_split *data )
{
	int	len;
	char	*name;

	name = NULL;
	len = ft_strlen(data->tokens[0]);
	if (!len)
		return (0);
	else if (len > 3 && !strncmp(data->tokens[0], "exit", len))
		return (-1);
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
	else	
		name = ms_file_exists(data->tokens[0], ms_getenv(*head, "PATH"));
	if (name)
	{
		printf("%s\n", name);
		printf("%d\n", execve(name, &name, NULL));
		free(name);
	}
	return (0);
}
