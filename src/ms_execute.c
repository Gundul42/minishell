/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:57:00 by graja             #+#    #+#             */
/*   Updated: 2021/10/27 11:49:23 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_execute(t_list **head, t_split *data )
{
	int	len;

	len = ft_strlen(data->tokens[0]);
	if (!strncmp(data->tokens[0], "exit", len))
		return (-1);
	if (!strncmp(data->tokens[0], "cd", len))
		ms_builtin_cd(head, data);
	if (!strncmp(data->tokens[0], "env", len))
		ms_builtin_env(head);
	if (!strncmp(data->tokens[0], "pwd", len))
		ms_builtin_pwd(head);
	return (0);
}
