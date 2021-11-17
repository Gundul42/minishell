/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:42:11 by graja             #+#    #+#             */
/*   Updated: 2021/11/16 13:43:13 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	chk_builtin(t_split *data, int len)
{
	if (!len)
		return (0);
	else if (len > 3 && !strncmp(data->tokens[0], "exit", len))
		return (1);
	else if (len > 1 && !strncmp(data->tokens[0], "cd", len))
		return (1);
	else if (len > 2 && !strncmp(data->tokens[0], "env", len))
		return (1);
	else if (len > 2 && !strncmp(data->tokens[0], "pwd", len))
		return (1);
	else if (len > 3 && !strncmp(data->tokens[0], "echo", len))
		return (1);
	else if (len > 5 && !strncmp(data->tokens[0], "export", len))
		return (1);
	else if (len > 4 && !strncmp(data->tokens[0], "unset", len))
		return (1);
	return (0);
}
