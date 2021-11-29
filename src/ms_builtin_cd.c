/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:52:00 by graja             #+#    #+#             */
/*   Updated: 2021/11/29 17:33:21 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	ms_update_dir(t_list **head)
{
	int		err;
	char	*new;

	err = 0;
	ms_print_error(head, NULL, 0);
	err = ms_putenv(head, "OLDPWD", ms_getenv(*head, "PWD"));
	if (!err)
	{
		new = getcwd(NULL, 0);
		err = ms_putenv(head, "PWD", new);
		free(new);
	}
	return (err);
}

static
char	*ms_checktilde(t_list **head, char *str)
{
	if (!ft_strlen(str) || *str != '~' || !ms_getenv(*head, "HOME"))
		return (ft_strdup(str));
	str++;
	return (ft_strjoin(ms_getenv(*head, "HOME"), str));
}

int	ms_builtin_cd(t_list **head, t_split *data)
{
	int		err;
	char	*new;

	if (!head || !data || !data->tokens[0])
		return (1);
	if (!ft_strlen(data->tokens[1]))
		err = chdir(ms_getenv(*head, "HOME"));
	else
	{
		new = ms_checktilde(head, data->tokens[1]);
		err = chdir(new);
		if (new)
			free(new);
	}
	if (err)
		ms_print_error(head, data->tokens[1], -1);
	else
	{
		err = ms_update_dir(head);
		ms_print_error(head, NULL, 0);
	}
	return (err);
}
