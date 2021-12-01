/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:57:47 by graja             #+#    #+#             */
/*   Updated: 2021/12/01 14:50:30 by graja            ###   ########.fr       */
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

static
void	ms_exp_error(t_list **head, char *tok)
{
	char	*front;

	front = ft_calloc(9 + ft_strlen(tok) + 1, sizeof(char));
	if (!front)
		return ;
	ft_strlcpy(front, "export: \'", 10);
	ft_strlcat(front, tok, 9 + ft_strlen(tok) + 1);
	ms_c_error(head, front, "\' is not a valid identifier", 1);
	free(front);
}

void	ms_builtin_export(t_list **head, t_split *data)
{
	char	**new;
	int		i;

	i = 1;
	ms_print_error(head, NULL, 0);
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
		else
			ms_exp_error(head, data->tokens[i]);
		i++;
	}
	if (i == 1)
		ms_printexp(head);
}
