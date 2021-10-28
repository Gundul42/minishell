/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:25:06 by graja             #+#    #+#             */
/*   Updated: 2021/10/28 18:38:56 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	ms_namecmp(t_list *lst, char *str)
{
	t_env	*ptr;

	ptr = (t_env *)lst->content;
	if (!ft_strncmp(str, ptr->name, ft_strlen(ptr->name)))
		return (1);
	return (0);
}

static
void	ms_delentry(void *lst)
{
	t_env	*cnt;

	cnt = (t_env *)(lst);
	if (cnt->name)
		free(cnt->name);
	if (cnt->value)
		free(cnt->value);
	free(cnt);
	printf("**DELETED**\n");
}

static
void	ms_unsetvar(t_list **head, char *str)
{
	t_list	**current;
	t_list	*next;
	int		i;

	i = 0;
	current = head;
	while (*current)
	{
		if (ms_namecmp(*current, str))
		{
			printf("Found %s in pos#%3d\n", str, i);
			next = (*current)->next;
			ft_lstdelone(*current, &ms_delentry);
			*current = next;
			break ;
		}
		i++;
		current = &(*current)->next;
	}
}

void	ms_builtin_unset(t_list **head, t_split *data)
{
	int		i;

	if (!data)
		return ;
	i = 1;
	while (ft_strlen(data->tokens[i]))
	{
		ms_unsetvar(head, data->tokens[i]);
		i++;
	}
	return ;
}
