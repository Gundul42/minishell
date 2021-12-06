/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:25:06 by graja             #+#    #+#             */
/*   Updated: 2021/11/29 17:38:43 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	ms_namecmp(t_list *lst, char *str)
{
	t_env	*ptr;

	ptr = (t_env *)lst->content;
	if (!ft_strncmp(str, ptr->name, ft_strlen(ptr->name) + 1))
		return (1);
	return (0);
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
			next = (*current)->next;
			ft_lstdelone(*current, &ms_delentry);
			*current = next;
			break ;
		}
		i++;
		current = &(*current)->next;
	}
}

static
int	ms_isvalid(char *s)
{
	while (s && *s)
	{
		if (!ft_isalnum(*s))
			return (0);
		s++;
	}
	return (1);
}

void	ms_delentry(void *lst)
{
	t_env	*cnt;

	cnt = (t_env *)(lst);
	if (cnt->name)
		free(cnt->name);
	if (cnt->value)
		free(cnt->value);
	free(cnt);
}

void	ms_builtin_unset(t_list **head, t_split *data)
{
	int		i;

	if (!data)
		return ;
	i = 1;
	while (ft_strlen(data->tokens[i]))
	{
		if (ms_isvalid(data->tokens[i]))
			ms_unsetvar(head, data->tokens[i]);
		else
		{
			printf("unset : \'%s\': not a valid", data->tokens[i]);
			printf(" identifier\n");
			ms_print_error(head, NULL, 1);
			break ;
		}
		i++;
	}
	return ;
}
