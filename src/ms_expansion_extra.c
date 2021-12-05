/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 11:52:37 by dmylonas          #+#    #+#             */
/*   Updated: 2021/12/05 11:58:07 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

char	*exp_var_extra(char *var, char *matrix, t_list **head)
{
	int		should_free;
	char	*new;
	int		entry;
	int		exit;
	char	*tmp;

	should_free = 0;
	entry = exp_findentry(matrix);
	exit = exp_findexit(matrix + entry + 1);
	if (var[0] == '?')
	{
		tmp = ft_itoa(g_status);
		should_free = 1;
	}
	else
		tmp = ms_getenv(*head, var);
	if (!tmp)
		tmp = "";
	new = exp_make(matrix, tmp, entry, exit);
	if (should_free == 1)
		free(tmp);
	return (new);
}
