/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cutter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:23:48 by graja             #+#    #+#             */
/*   Updated: 2021/11/11 10:42:04 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
char	*runtilfree(char *str, char c)
{
	while (*str && *str != c)
		str++;
	if (*str)
		str++;
	return (str);
}

static
char	*jumpspace(char *str)
{
	while (*str == 32 || (*str > 7 && *str < 14))
		str++;
	return (str);
}

static
char	*cuttoken(char *bgn, char *end)
{
	int		len;
	char	*token;

	len = (int)(end - bgn);
	token = ft_calloc(len + 1, sizeof(char));
	if (!len || !token)
		return (NULL);
	token = memcpy(token, bgn, len);
	return (token);
}

static
void	fillmatrix(char **matrix, char *bgn, char *end, int i)
{
	while (matrix && *end && *end != '#')
	{
		if (*end == 32)
		{
			matrix[i] = cuttoken(bgn, end);
			end = jumpspace(end);
			bgn = end;
			i++;
		}
		else if (*end == '"' || *end == '\'')
		{
			end = runtilfree(end + 1, *end);
			matrix[i] = cuttoken(bgn, end);
			end = jumpspace(end);
			bgn = end;
			i++;
		}
		else
			end++;
	}
	matrix[i] = cuttoken(bgn, end);
}

char	**ms_cut_tokens(char *str, t_list **head)
{
	char	**matrix;
	int		i;

	matrix = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	fillmatrix(matrix, str, str, 0);
	expand_envvars(matrix, head);
	i = 0;
	while (matrix[i])
	{
		printf("%s<<<\n", matrix[i]);
		i++;
	}
	return (matrix);
}
