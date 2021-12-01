/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:26:28 by dmylonas          #+#    #+#             */
/*   Updated: 2021/12/01 11:57:11 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* global var to hold error nbr of signals
 * no other solution found than using globals */
int	g_ms_sigerr = -1;

void	ms_free_env(t_list **head, int flag)
{
	t_list	**current;
	t_list	*next;
	int		i;

	i = 0;
	current = head;
	while (*current)
	{
		next = (*current)->next;
		if (!flag)
			ft_lstdelone(*current, &ms_delentry);
		else
			ft_lstdelone(*current, &ms_del_cmd);
		*current = next;
		i++;
	}
	free(head);
}

void	ms_init_shell(t_list **head, t_list **lsthead)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = ms_getprompt(*head);
		define_input_signals(head);
		input = readline(prompt);
		if (!input)
		{
			free(prompt);
			ms_exit(head, lsthead);
		}
		free(prompt);
		if (!ft_strlen(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		scan_input(input, head, lsthead);
		ms_read_arguments(lsthead);
		ms_execute(head, lsthead);
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
	ms_welcome();
	ms_init_env(ehead, environ);
	ms_putenv(ehead, "?", "0");
	ms_init_shell(ehead, lsthead);
	return (0);
}
