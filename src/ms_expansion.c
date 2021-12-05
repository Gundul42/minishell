/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:48:10 by graja             #+#    #+#             */
/*   Updated: 2021/12/05 11:58:03 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void	exp_var(char **matrix, int i, t_list **head)
{
	int		entry;
	int		exit;
	char	*var;
	char	*new;

	entry = exp_findentry(matrix[i]);
	exit = exp_findexit(matrix[i] + entry + 1);
	var = ft_substr(matrix[i], entry + 1, exit);
	if (!ft_strlen(var))
	{
		free(var);
		return ;
	}
	new = exp_var_extra(var, matrix[i], head);
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
