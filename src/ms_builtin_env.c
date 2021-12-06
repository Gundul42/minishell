/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:09:07 by graja             #+#    #+#             */
/*   Updated: 2021/11/29 12:31:04 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_builtin_env(t_list **list)
{
	t_env	*ptr;
	t_list	*head;

	if (!list)
		return (1);
	head = *list;
	while (head)
	{
		ptr = (t_env *)(head->content);
		printf("%s=", ptr->name);
		if (ptr->value)
			printf("%s\n", ptr->value);
		else
			printf("\n");
		head = head->next;
	}
	ms_print_error(list, NULL, 0);
	return (0);
}
