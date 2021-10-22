/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:32:42 by graja             #+#    #+#             */
/*   Updated: 2021/10/22 15:34:40 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	parse(char **str)
{
	pid_t	pid;
	int		status;

	if (!str)
		return ;
	if (!ft_strncmp(str[0], "ls\0", 3))
	{
		printf("CMD: %s\n", str[0]);
		pid = fork();
		if (!pid)
		{
			execve(str[0], str, NULL);
			_exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, &status, 0);
	}
}
