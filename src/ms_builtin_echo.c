/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:46:07 by graja             #+#    #+#             */
/*   Updated: 2021/11/05 15:15:03 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_builtin_echo(t_split *data)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_strlen(data->tokens[1]) == 0)
		return ;
	if (!ft_strncmp(data->tokens[1], "-n", ft_strlen(data->tokens[1])))
	{
		flag = 1;
		i++;
	}
	while (i < 50)
	{
		if (ft_strlen(data->tokens[i]) == 0)
			break ;
		if (i > 1 || (flag && i > 2))
			printf("%s", data->tokens[i]);
		else
			printf("%s", data->tokens[i]);
		i++;
	}
	if (!flag)
		printf("\n");
}
