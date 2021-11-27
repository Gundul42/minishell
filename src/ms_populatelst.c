/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_populatelst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:51:27 by graja             #+#    #+#             */
/*   Updated: 2021/11/27 14:18:52 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	get_numbr_token(char **matrix, int i)
{
	int	n;

	n = 0;
	while (matrix && matrix[i])
	{
		if (!ft_strncmp(matrix[i], "|\0", 2))
			break ;
		if (ft_strlen(matrix[i]))
			n++;
		i++;
	}
	return (n);
}

static
void	cpy_tokens(char **matrix, char **new, int i, int n)
{
	int	j;

	if (!new)
		return ;
	j = 0;
	while (j < n && matrix[i + j])
	{
		if (matrix[i + j][0] == '\"')
			new[j] = ft_strtrim(matrix[i + j], "\"");
		else
			new[j] = ft_strtrim(matrix[i + j], "\'");
		free(matrix[i + j]);
		j++;
	}
	new[j] = NULL;
}

/* this is building the execution list with the pipe sign | as
 * separator. If it runs out of memory it breaks. All needed memory
 * is allocated und all uneeded from matrix is freed */
void	ms_populate_cmdlst(char **matrix, t_list **lsthead)
{
	t_split	*content;
	int		i;
	int		n;

	i = 0;
	while (matrix && matrix[i])
	{
		n = get_numbr_token(matrix, i);
		if (n)
		{
			content = ft_calloc(1, sizeof(t_split));
			if (!content)
				return ;
			content->tokens = ft_calloc(n + 1, sizeof(char *));
			cpy_tokens(matrix, content->tokens, i, n);
			ft_lstadd_back(lsthead, ft_lstnew(content));
			i += n;
		}
		else
		{
			free(matrix[i]);
			i++;
		}
	}
}
