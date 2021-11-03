/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_enviro_hlp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:58:10 by graja             #+#    #+#             */
/*   Updated: 2021/11/03 14:45:18 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	ms_getlen(char *str)
{
	int	i;

	i = 0;
	while (*str && *str != '=')
	{
		i++;
		str++;
	}
	return (i);
}

/* returns the number of entries in the env list */
int	ms_getenvnbr(t_list **head)
{
	int		i;
	t_list	*ptr;

	ptr = *head;
	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

/*splits the string after first equal sign in two parts*/
char	**ms_split(char	*str)
{
	char	**new;
	int		len;

	if (!str || !*str)
		return (NULL);
	len = ms_getlen(str);
	new = ft_calloc(2, sizeof(char));
	if (!new)
		return (NULL);
	new[0] = calloc(len + 1, sizeof(char));
	if (!new[0])
		return (NULL);
	new[0] = ft_memcpy(new[0], str, len);
	len = ft_strlen(str) - 1 - len;
	if (len)
		new[1] = calloc(len + 1, sizeof(char));
	else
		new[1] = NULL;
	if (new[1])
		new[1] = ft_memcpy(new[1], str + ft_strlen(new[0]) + 1, len);
	return (new);
}
