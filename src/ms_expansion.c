/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:48:10 by graja             #+#    #+#             */
/*   Updated: 2021/12/03 11:46:06 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	exp_findentry(char *str)
{
	int	n;

	n = 0;
	while (*str && *(str + 1) && chk_single(str))
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
	if (*str && *str == '?')
		return (1);
	while (*str && ft_isalnum(*str))
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
	{
		new = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(new, old, entry);
		ft_strlcat(new, old + entry + exit + 1, len);
		return (new);
	}
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, old, entry + 1);
	ft_strlcat(new, insert, ft_strlen(new) + ft_strlen(insert) + 1);
	ft_strlcat(new, old + entry + exit + 1, len);
	return (new);
}

void	exp_var(char **matrix, int i, t_list **head)
{
	int		entry;
	int		exit;
	char	*var;
	char	*new;
	char	*tmp;

	entry = exp_findentry(matrix[i]);
	exit = exp_findexit(matrix[i] + entry + 1);
	var = ft_substr(matrix[i], entry + 1, exit);
	if (!ft_strlen(var))
	{
		free(var);
		return ;
	}
	tmp = ms_getenv(*head, var);
	if (!tmp)
		tmp = "";
	new = exp_make(matrix[i], tmp, entry, exit);
	free(var);
	free(matrix[i]);
	matrix[i] = new;
}

void	expand_envvars(char **matrix, t_list **head)
{
	int		i;
	int		n;
	char	*run;

	i = 0;
	while (matrix[i])
	{
		if (expand_or_not(matrix, i))
		{
			n = 0;
			run = matrix[i];
			while (run && *run)
			{
				if (*run == '$')
					n++;
				run++;
			}
			while (n)
			{
				exp_var(matrix, i, head);
				n--;
			}
		}
		i++;
	}
}
