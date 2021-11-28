/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:59:17 by graja             #+#    #+#             */
/*   Updated: 2021/11/28 12:20:06 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void	ms_read_arguments(t_list **lsthead)
{
	t_list	*lst;
	t_split	*content;
	int		i;
	int		ttl;

	lst = *lsthead;
	while (lst)
	{
		content = (t_split *)(lst->content);
		ttl = get_ttl(content->tokens);
		i = 0;
		while (i < ttl)
		{
			i = ms_check_token_input(content, i);
			i = ms_check_token_output(content, i);
			i++;
		}
		sort_back(content->tokens, ttl);
		lst = lst->next;
	}
}
