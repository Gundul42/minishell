/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:46:07 by graja             #+#    #+#             */
/*   Updated: 2021/12/01 01:03:37 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	ms_check_echoflag(char *s)
{
	if (!s || *s != '-')
		return (0);
	s++;
	while (*s)
	{
		if (*s != 'n')
			return (0);
		s++;
	}
	return (1);
}

void	ms_builtin_echo(t_list **head, t_split *data)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (ms_check_echoflag(data->tokens[i]))
	{
		flag++;
		i++;
	}
	while (data->tokens[i])
	{
		if (ft_strlen(data->tokens[i]) != 0)
		{
			if ((!flag && i > 1) || (flag && i > flag + 1))
				printf(" %s", data->tokens[i]);
			else
				printf("%s", data->tokens[i]);
		}
		i++;
	}
	if (!flag)
		printf("\n");
	ms_print_error_for_glob(NULL, 0);
	// ms_print_error(head, NULL, 0);
}
