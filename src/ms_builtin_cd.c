/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:52:00 by graja             #+#    #+#             */
/*   Updated: 2021/10/26 18:36:01 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
char	*ms_checktilde(t_list **head, char *str)
{
	if (!ft_strlen(str) || *str != '~')
		return (str);
	str++;
	return (ft_strjoin(ms_getenv(*head, "HOME"), str));
}

int	ms_builtin_cd(t_list **head, t_split *data)
{
	int	err;

	if (!head || !data || !data->tokens[1])
		return (1);
	if (!ft_strlen(data->tokens[1]))
		err = chdir(ms_getenv(*head, "HOME"));
	else
		err = chdir(ms_checktilde(head, data->tokens[1]));
	if (err)
		return (err);
	err = ms_putenv(head, "OLDPWD", ms_getenv(*head, "PWD"));
	if (!err)
		err = ms_putenv(head, "PWD", getcwd(NULL, 0));
	return (err);
}
