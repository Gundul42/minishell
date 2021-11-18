/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:26:28 by dmylonas          #+#    #+#             */
/*   Updated: 2021/11/18 09:01:20 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
void	ms_free_env(t_list **head)
{
	t_list	**current;
	t_list	*next;
	int		i;

	i = 0;
	current = head;
	while (*current)
	{
		next = (*current)->next;
		ft_lstdelone(*current, &ms_delentry);
		*current = next;
		i++;
	}
	free(head);
}

// Greeting shell during startup
void	ms_init_shell(t_list **head, t_list **lsthead)
{
	char	*input;
	char	*prompt;
	int		err;

	err = 0;
	while (err >= 0)
	{
		prompt = ms_getprompt(*head);
		input = readline(prompt);
		if (!input)
		{
			free(prompt);
			return ;
		}
		free(prompt);
		if (ft_strlen(input))
			add_history(input);
		scan_input(input, head, lsthead);
		ms_read_arguments(lsthead);
		err = ms_execute(head, lsthead);
	}
}

int	main(void)
{
	t_list		**ehead;
	t_list		**lsthead;
	extern char	**environ;

	ehead = malloc(sizeof(t_list *));
	lsthead = malloc(sizeof(t_list *));
	if (!lsthead || !ehead)
		return (1);
	*ehead = NULL;
	*lsthead = NULL;
	ms_init_env(ehead, environ);
	ms_init_shell(ehead, lsthead);
	ms_free_env(ehead);
	return (0);
}
