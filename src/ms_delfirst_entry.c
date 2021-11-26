/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_delfirst_entry.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:28:56 by graja             #+#    #+#             */
/*   Updated: 2021/11/26 10:44:31 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_del_cmd(void *lst)
{
	t_split	*content;
	int		i;

	i = 0;
	content = (t_split *)(lst);
	if (!content)
		return ;
	while (content->tokens[i])
	{
		free(content->tokens[i]);
		i++;
	}
	if (content->tokens)
		free(content->tokens);
	if (content->iname)
		free(content->iname);
	if (content->oname)
		free(content->oname);
	free(content);
}

void	ms_delfirst_entry(t_list **head)
{
	t_list	**current;
	t_list	*next;

	current = head;
	if (!*current)
		return ;
	next = (*current)->next;
	ft_lstdelone(*current, &ms_del_cmd);
	*current = next;
	current = &(*current)->next;
}
