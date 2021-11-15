/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:45:58 by graja             #+#    #+#             */
/*   Updated: 2021/11/15 14:02:53 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	init_pipes(t_list **lsthead)
{
	int	size;
	int	i;
	int	*fd;
	t_split	*content;
	t_list	*run;

	size = ft_lstsize(*lsthead);
	fd = calloc(size, sizeof(int));
	i = 0;
	run = *lsthead;
	while (i < size)
	{
		content = (t_split *)(run->content);
		content->piped = size - 1;
		content->pipenbr = i;
		content->pipefd = fd;
		i++;
		run = run->next;
	}
}
