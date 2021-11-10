/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:48:10 by graja             #+#    #+#             */
/*   Updated: 2021/11/10 18:53:56 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	exp_findentry(char *str)
{
	int	n;

	n = 0;
	while (*str && *str!= '$')
	{
		str++;
		n++;
	}
	return (n);
}

static
int	exp_findexit(char *str)
{
	int	n;

	n = 0;
	while (*str && *str != '"' && *str != '\'' && *str != ' '
			&& *str != '$')
	{
		str++;
		n++;
	}
	return (n);
}

static
char	*exp_make(char *old, char *insert, int entry, int exit)
{
	char	*new;
	int		len;

	len = ft_strlen(old);
	if (insert)
		len += ft_strlen(insert);
	else
		insert = "\0";
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, old, entry + 1);
	ft_strlcat(new, insert, ft_strlen(new) + ft_strlen(insert) + 1);
	ft_strlcat(new, old + entry + exit + 1, len);
	return (new);
}

static
void	exp_var(char **matrix, int i, t_list **head)
{
	int	entry;
	int	exit;
	char	*var;
	char	*new;

	entry = exp_findentry(matrix[i]);
	exit = exp_findexit(matrix[i] + entry + 1);
	var = ft_substr(matrix[i], entry + 1, exit);
	new = exp_make(matrix[i], ms_getenv(*head, var), entry, exit);
	free(var);
	free(matrix[i]);
	matrix[i] = new;
}

void	expand_envvars(char **matrix, t_list **head)
{
	int		i;

	i = 0;
	while (matrix[i])
	{
		if (*matrix[i] != '\'')
		{
			while (ft_strchr(matrix[i], '$'))
			exp_var(matrix, i, head);
		}
		i++;
	}
}
