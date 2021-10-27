/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:25:06 by graja             #+#    #+#             */
/*   Updated: 2021/10/27 19:05:17 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	ms_builtin_unset(t_list **head, t_split *data)
{
	t_list	*cpy;

	cpy = *head;
	if (!data)
		return ;
	while (*head)
		*head = (*head)->next;
	printf("END\n");
	*head = cpy;
	return ;
}
