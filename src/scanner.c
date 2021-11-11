/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:22:03 by graja             #+#    #+#             */
/*   Updated: 2021/11/11 17:15:11 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* all trailing and ending whitespaces are cut of */
static
char	*cleanup(char *input)
{
	char	*help;

	help = ft_strtrim(input, " \t\r\n\v\f");
	if (!help)
		return (NULL);
	free (input);
	return (help);
}

/* when a single quto comes first do not expand env vars */
int	expand_or_not(char **matrix, int i)
{
	int	j;

	j = 0;
	while (matrix[i][j] && matrix[i][j] != '$' && matrix[i][j] != '"')
	{
		if (matrix[i][j] == '\'')
			return (0);
		j++;
	}
	return (1);
}

/* this is looking for single $ followed by space or more $s */
int	chk_single(char *str)
{
	if (ft_strlen(str) < 2)
		return (1);
	if (*str == '$' && ft_isalnum(*(str + 1)))
		return (0);
	return (1);
}

void	scan_input(char *input, t_list **head)
{
	if (!input)
		return ;
	check_and_insert_spaces(&input);
	input = cleanup(input);
	printf("Trimmed: >>>%s\n", input);
	ms_cut_tokens(input, head);
	free(input);
}
