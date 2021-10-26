/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_enviro_hlp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:58:10 by graja             #+#    #+#             */
/*   Updated: 2021/10/26 18:37:20 by graja            ###   ########.fr       */
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
