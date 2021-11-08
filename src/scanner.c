/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:22:03 by graja             #+#    #+#             */
/*   Updated: 2021/11/08 18:54:32 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
char	cut_comments(char *input)
{
	char	*bkp;
	int	quote;

	quote = 0;


/* check for missing quotes */
static
int	checkquote( char *input, char c)
{
	char	*bck;
	int	err;

	bck = input;
	while (*bck)
	{
		if (!c && *bck == '"')
			err = checkquote(bck, '"');

	return (0);
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
	input = cut_comments(input);
	printf("Trimmed: >>>%s\n", input);
	return (input);
}
