/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:22:38 by graja             #+#    #+#             */
/*   Updated: 2021/11/28 08:53:02 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_exit(t_list **env, t_list **ctt)
{
	int	nbr;

	nbr = ft_atoi(ms_getenv(*env, "?"));
	if (env)
		ms_free_env(env, 0);
	if (ctt)
		ms_free_env(ctt, 1);
	exit(nbr);
}

void	ms_exit_cmd(t_list **head, t_list **ctt, t_split *data)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (data->tokens[i])
	{
		if (ft_atoi(data->tokens[i]))
			n++;
		i++;
	}
	if (n > 1)
	{
		printf("exit: too many arguments\n");
		ms_print_error(head, NULL, 1);
		return ;
	}
	if (i > 1)
		ms_print_error(head, NULL, ft_atoi(data->tokens[1]));
	ms_exit(head, ctt);
}
