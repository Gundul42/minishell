/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:09:07 by graja             #+#    #+#             */
/*   Updated: 2021/12/05 10:58:13 by dmylonas         ###   ########.fr       */
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
	ms_print_error_for_glob(NULL, 0);
	return (0);
}
