/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:46:07 by graja             #+#    #+#             */
/*   Updated: 2021/11/14 13:58:34 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_builtin_echo(t_split *data)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_strlen(data->tokens[1]) == 2 && !ft_strncmp(data->tokens[1], "-n\0", 3))
	{
		flag = 1;
		i++;
	}
	while (data->tokens[i])
	{
		if (ft_strlen(data->tokens[i]) != 0)
		{
			if (i > 1 || (flag && i > 2))
				printf(" %s", data->tokens[i]);
			else
				printf("%s", data->tokens[i]);
		}
		i++;
	}
	if (!flag)
		printf("\n");
}
