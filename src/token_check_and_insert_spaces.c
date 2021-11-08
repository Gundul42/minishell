/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check_and_insert_spaces.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:39:54 by dmylonas          #+#    #+#             */
/*   Updated: 2021/11/08 11:14:12 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static char	*create_new_line(char *line, char *current,
		int operator_size, int offset)
{
	char	*left;
	char	*operator;
	char	*right;
	char	*new_line;
	char	*joined1;
	char	*joined2;
	char	*joined3;

	left = ft_substr(line, 0, offset);
	operator = ft_substr(current, 0, operator_size);
	right = ft_strdup(current + operator_size);
	joined1 = ft_strjoin(left, " ");
	joined2 = ft_strjoin(joined1, operator);
	joined3 = ft_strjoin(joined2, " ");
	new_line = ft_strjoin(joined3, right);
	free(left);
	free(operator);
	free(right);
	free(joined1);
	free(joined2);
	free(joined3);
	
	return (new_line);
}

static char	*insert_spaces(char **line, char *current, char *line_initial)
{
	char	*new_line;
	int		operator_size;
	int		offset;

	if (current != line_initial)
		if (*(current - 1) == '>' || *(current - 1) == '<')
			return (current++);
	if (*current == *(current + 1))
		operator_size = 2;
	else
		operator_size = 1;
	//e.g. lol>fsa -> offset = 3, because > is in position 3
	offset = current - *line;
	new_line = create_new_line(*line, current, operator_size, offset);
	free(*line);
	*line = new_line;
	return (new_line + offset + operator_size + 1);
}

static int	is_operator(char *value)
{
	if (!(ft_strncmp(value, "|", 1)))
		return (1);
	if (!(ft_strncmp(value, ">>", 2)) || !(ft_strncmp(value, "<<", 2)))
		return (1);
	if (!(ft_strncmp(value, ">", 1)) || !(ft_strncmp(value, "<", 1)))
		return (1);
	return (0);
}

void	check_and_insert_spaces(char **line)
{
	char	*current;
	char	*line_initial;
	char	quote_found;

	current = *line;
	line_initial = *line;
	while (current && *current)
	{
		// if there're quotes i just move after them
		if ((*current == '\'' && ft_strchr(current + 1, '\'')) 
			|| ((*current == '"' && ft_strchr(current + 1, '"'))))
		{
			quote_found = *current;
			current++;
			while (*current != quote_found)
				current++;
		}
		if (is_operator(current))
			current = insert_spaces(line, current, line_initial);
		current++;
	}
}
