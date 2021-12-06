/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check_and_insert_spaces.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:39:54 by dmylonas          #+#    #+#             */
/*   Updated: 2021/12/04 14:09:42 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
char	*create_new_line(char *line, char *current,
		int operator_size, int offset)
{
	char	**help;
	char	*new_line;

	help = ft_calloc(6, sizeof(char *));
	if (!help)
		return (NULL);
	help[0] = ft_substr(line, 0, offset);
	help[1] = ft_substr(current, 0, operator_size);
	help[2] = strdup(current + operator_size);
	help[3] = ft_strjoin(help[0], " ");
	help[4] = ft_strjoin(help[3], help[1]);
	help[5] = ft_strjoin(help[4], " ");
	new_line = ft_strjoin(help[5], help[2]);
	free(help[0]);
	free(help[1]);
	free(help[2]);
	free(help[3]);
	free(help[4]);
	free(help[5]);
	free(help);
	return (new_line);
}

static
int	is_operator(char *value)
{
	if (!(ft_strncmp(value, "|", 1)))
	{
		if (ft_isalnum(*(value + 1)))
			return (1);
	}
	if (!(ft_strncmp(value, ">>", 2)) || !(ft_strncmp(value, "<<", 2)))
	{
		if (ft_isalnum(*(value + 2)))
			return (1);
	}
	if (!(ft_strncmp(value, ">", 1)) || !(ft_strncmp(value, "<", 1)))
	{
		if (ft_isalnum(*(value + 1)))
			return (1);
	}
	return (0);
}

static
char	*insert_spaces(char **line, char *current, char *line_initial)
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
	offset = current - *line;
	new_line = create_new_line(*line, current, operator_size, offset);
	free(*line);
	*line = new_line;
	return (new_line + offset + operator_size + 1);
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
