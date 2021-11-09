/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:22:03 by graja             #+#    #+#             */
/*   Updated: 2021/11/09 15:23:34 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	checkstack(char *stack, int run, char c)
{
	if (!stack[run])
	{
		stack[run] = c;
		return (run);
	}
	else if (stack[run] == c)
	{
		stack[run] = '\0';
		return (run -1);
	}
	else
	{
		stack[run + 1] = c;
		return (run + 1);
	}
}

/* check for missing quotes */
static
int	checkquote(char *str)
{
	char	*stack;
	int	run;

	run = 0;
	stack = calloc(ft_strlen(str) + 1, sizeof(char));
	if (!stack)
		return (1);
	while (*str)
	{
		if (*str =='\'' || *str == '"')
			run = checkstack(stack, run, *str);
		str++;
		if (run < 0)
			run = 0;
	}
	run = ft_strlen(stack);
	free(stack);
	return (run);
}

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

char	*scan_input(char *input)
{
	int	err;

	err = 0;
	if (!input)
		return (NULL);
	check_and_insert_spaces(&input);
	input = cleanup(input);
	err = checkquote(input);
	if (err)
	{
		free(input);
		printf("Syntax Error: unclosed quote\n");
		return (NULL);
	}
	printf("Trimmed: >>>%s\n", input);
	return (input);
}
