/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:59:17 by graja             #+#    #+#             */
/*   Updated: 2021/12/03 15:40:23 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
void	ms_syntax_error(t_list **head)
{
	t_list	**current;
	t_list	*next;

	current = head;
	while (*current)
	{
		next = (*current)->next;
		ft_lstdelone(*current, &ms_del_cmd);
		*current = next;
	}
	*head = NULL;
	ms_delfirst_entry(head);
}

static
int	get_ttl(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static
void	sort_back(char **arr, int ttl)
{
	int	i;
	int	j;

	i = 0;
	while (i < ttl)
	{
		if (!arr[i])
		{
			j = i + 1;
			while (j < ttl)
			{
				if (arr[j])
				{
					arr[i] = ft_strdup(arr[j]);
					free(arr[j]);
					arr[j] = NULL;
					break ;
				}
				j++;
			}
		}
		i++;
	}
}

int	ms_read_arguments(t_list **lsthead, int i, int ttl)
{
	t_list	*lst;
	t_split	*content;

	lst = *lsthead;
	while (lst)
	{
		content = (t_split *)(lst->content);
		ttl = get_ttl(content->tokens);
		i = 0;
		while (i < ttl && i >= 0)
		{
			i = ms_check_token_input(content, i);
			if (i >= 0)
				i = ms_check_token_output(content, i);
			i++;
		}
		sort_back(content->tokens, ttl);
		if (i < 0)
		{
			ms_syntax_error(lsthead);
			return (666);
		}
		lst = lst->next;
	}
	return (0);
}
