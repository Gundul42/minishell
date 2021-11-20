/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:45:58 by graja             #+#    #+#             */
/*   Updated: 2021/11/20 14:42:03 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	do_init(int i, int *fd, int size)
{
	if (i < size - 1)
	{
		if (pipe(fd + i * 2) == -1)
			return (2);
	}
	return (0);
}

int	init_pipes(t_list **lsthead)
{
	int		size;
	int		i;
	int		*fd;
	t_split	*content;
	t_list	*run;

	size = ft_lstsize(*lsthead);
	fd = calloc((size - 1) * 2, sizeof(int));
	if (!fd)
		return (1);
	i = 0;
	run = *lsthead;
	while (i < size)
	{
		content = (t_split *)(run->content);
		content->piped = size - 1;
		content->pipenbr = i;
		content->pipefd = fd;
		if (do_init(i, fd, size))
			return (2);
		i++;
		run = run->next;
	}
	return (0);
}
