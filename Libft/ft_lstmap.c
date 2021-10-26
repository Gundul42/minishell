/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:18:01 by graja             #+#    #+#             */
/*   Updated: 2021/05/24 13:18:31 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* first check if the functions pointer actually work or are still void */
/* init head, which is the pointer to the first element of the new list */
/* loop until lst is NULL and check if allocating of ft_newlist was suc */
/* cesful. If it was succesfull add the new element to the tail of the  */
/* new list head is pointing to. loop until last entry of lst           */
/* If allocating of newlist was unsuccessful free everything and exit   */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*head;

	if (!f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		newlist = ft_lstnew(f(lst->content));
		if (newlist == NULL)
		{
			while (head)
			{
				newlist = head->next;
				del(head->content);
				free(head);
				head = newlist;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&head, newlist);
		lst = lst->next;
	}
	return (head);
}
