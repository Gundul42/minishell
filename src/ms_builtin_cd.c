/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:52:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/14 10:21:01 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
char	*ms_checktilde(t_list **head, char *str)
{
	if (!ft_strlen(str) || *str != '~' || !ms_getenv(*head, "HOME"))
		return (str);
	str++;
	return (ft_strjoin(ms_getenv(*head, "HOME"), str));
}

int	ms_builtin_cd(t_list **head, t_split *data)
{
	int	err;

	if (!head || !data || !data->tokens[0])
		return (1);
	if (!ft_strlen(data->tokens[1]))
		err = chdir(ms_getenv(*head, "HOME"));
	else
		err = chdir(ms_checktilde(head, data->tokens[1]));
	if (err)
	{
		printf("%s: not found\n", data->tokens[1]);
		return (err);
	}
	err = ms_putenv(head, "OLDPWD", ms_getenv(*head, "PWD"));
	if (!err)
		err = ms_putenv(head, "PWD", getcwd(NULL, 0));
	return (err);
}
