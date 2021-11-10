/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sortenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:55:52 by graja             #+#    #+#             */
/*   Updated: 2021/11/10 12:56:12 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	ms_compare(char *one, char *two)
{
	int	i;

	i = 0;
	while (one && two)
	{
		if (one[i] > two[i])
			return (1);
		else if (one[i] < two[i])
			return (0);
		else if (one[i] == two[i])
			i++;
	}
	return (0);
}

static
void	ms_bubble(t_env **lst, int nbr)
{
	t_env	*temp;
	int		swapped;
	int		run;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		run = 0;
		while (run < nbr - 1)
		{
			if (ms_compare(lst[run]->name, lst[run + 1]->name))
			{
				temp = lst[run];
				lst[run] = lst[run + 1];
				lst[run + 1] = temp;
				swapped = 1;
			}
			run++;
		}
	}
}

t_env	**ms_sortenv(t_list **head)
{
	t_list	*lst;
	t_env	**ret;
	int		i;

	i = 0;
	ret = calloc(ms_getenvnbr(head) + 1, sizeof(t_env *));
	if (!ret)
		return (NULL);
	lst = *head;
	while (lst)
	{
		ret[i] = (t_env *)(lst->content);
		i++;
		lst = lst->next;
	}
	ret[i] = NULL;
	ms_bubble(ret, ms_getenvnbr(head));
	return (ret);
}
