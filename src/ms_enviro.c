/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_enviro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:16:28 by graja             #+#    #+#             */
/*   Updated: 2021/11/26 09:04:39 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* changes the value of ENV-VAR name to the value val
 * if no such ENV-VAR exists it will be created and
 * the value set
 * returns 0 on success and 1 on failure
 */
int	ms_putenv(t_list **head, char *name, char *val)
{
	t_env	*ptr;
	t_list	*iter;

	iter = *head;
	while (iter)
	{
		ptr = (t_env *)(iter->content);
		if (!ft_strncmp(ptr->name, name, ft_strlen(name) + 1))
			break ;
		iter = iter->next;
	}
	if (iter)
	{
		free(ptr->value);
		ptr->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
		ptr->value = ft_memcpy(ptr->value, val, ft_strlen(val));
	}
	else
		return (ms_insnewlst(head, name, val));
	if (ptr->value)
		return (0);
	else
		return (1);
}

/* returns the value of ENV-VAR name as a string
 * returns NULL if non existant
 */
char	*ms_getenv(t_list *head, char *str)
{
	t_env	*val;

	if (!head || !str)
		return (NULL);
	while (head)
	{
		val = (t_env *)(head->content);
		if (!strncmp(val->name, str, ft_strlen(str) + 1))
			return (val->value);
		head = head->next;
	}
	return (NULL);
}

int	ms_insnewlst(t_list **head, char *name, char *val)
{
	t_env	*content;

	content = malloc(sizeof(t_env));
	if (!head || !name || !val || !content)
		return (1);
	content->name = ft_calloc(ft_strlen(name) + 1, sizeof(char));
	content->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
	if (!content->name || !content->value)
		return (1);
	content->name = ft_memcpy(content->name, name, ft_strlen(name));
	content->value = ft_memcpy(content->value, val, ft_strlen(val) + 1);
	ft_lstadd_back(head, ft_lstnew(content));
	return (0);
}

int	ms_add2list(t_list **ehead, char *str)
{
	t_env	*content;
	char	**rst;

	content = malloc(sizeof(t_env));
	if (!ehead || !str || !content)
		return (1);
	rst = ms_split(str);
	if (!rst)
		return (1);
	content->name = rst[0];
	content->value = rst[1];
	ft_lstadd_back(ehead, ft_lstnew(content));
	free(rst);
	return (0);
}

/* init the ENV and load everything in a linked list
 * ehead points to the head, *ehead is the head
 * returns 0 on success, 1 on failure
 */
int	ms_init_env(t_list **ehead, char **env)
{
	int	err;
	int	i;

	err = 0;
	i = 0;
	while (!err && env && env[i])
	{
		err = ms_add2list(ehead, env[i]);
		i++;
	}
	if (!env || !i)
		err = 1;
	return (err);
}
