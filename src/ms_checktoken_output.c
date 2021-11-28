/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checktoken_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 12:09:23 by graja             #+#    #+#             */
/*   Updated: 2021/11/28 12:18:23 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
void	ms_set_ctto(t_split *content, int i, int flag)
{
	if (flag)
		content->appo = 1;
	else
		content->redo = 1;
	if (content->oname)
		free(content->oname);
	content->oname = ft_strdup(content->tokens[i + 1]);
	free(content->tokens[i]);
	free(content->tokens[i + 1]);
	content->tokens[i] = NULL;
	content->tokens[i + 1] = NULL;
}

int	ms_check_token_output(t_split *content, int i)
{
	if (!content->tokens[i])
		return (i);
	if (!ft_strncmp(content->tokens[i], ">>", 3))
	{
		ms_set_ctto(content, i, 1);
		return (i + 1);
	}
	else if (!ft_strncmp(content->tokens[i], ">", 2))
	{
		ms_set_ctto(content, i, 0);
		return (i + 1);
	}
	return (i);
}
