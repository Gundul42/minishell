/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:57:47 by graja             #+#    #+#             */
/*   Updated: 2021/12/01 01:04:20 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
int	ms_hasequal(char *str)
{
	if (str && (ft_strlen(str) < 3 || !ft_isalpha(*str)))
		return (0);
	while (str && *str)
	{
		if (!ft_isalnum(*str) && *str != '=')
			return (0);
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

static
void	ms_printexp(t_list **head)
{
	t_env	**ptr;
	int		i;

	i = 0;
	ptr = ms_sortenv(head);
	while (ptr && ptr[i])
	{
		printf("declare -x ");
		printf("%s=\"", ptr[i]->name);
		if (ms_getenv(*head, ptr[i]->name))
			printf("%s\"\n", ms_getenv(*head, ptr[i]->name));
		else
			printf("\"\n");
		i++;
	}
	free(ptr);
}

static
char	*trimmer(char *old)
{
	char	*new;

	if (old[0] == '\"')
		new = ft_strtrim(old, "\"");
	else if (old[0] == '\'')
		new = ft_strtrim(old, "\'");
	else
		return (old);
	free(old);
	return (new);
}

void	ms_builtin_export(t_list **head, t_split *data)
{
	char	**new;
	int		i;

	i = 1;
	while (ft_strlen(data->tokens[i]))
	{
		if (ms_hasequal(data->tokens[i]))
		{
			new = ms_split(data->tokens[i]);
			if (new[0] && new[1])
			{
				new[1] = trimmer(new[1]);
				ms_putenv(head, new[0], new[1]);
				free(new[0]);
				free(new[1]);
				free(new);
			}
		}
		i++;
	}
	if (i == 1)
		ms_printexp(head);
	// ms_print_error(head, NULL, 0);
	ms_print_error_for_glob(NULL, 0);
}
