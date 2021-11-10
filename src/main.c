/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:26:28 by dmylonas          #+#    #+#             */
/*   Updated: 2021/11/10 13:38:00 by graja            ###   ########.fr       */
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
void	ms_init_shell(t_list **head)
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
		input = scan_input(input);
		if (input)
			free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_list	**ehead;

	ehead = malloc(sizeof(t_list *));
	if (!ehead || !argc || !argv)
		return (1);
	*ehead = NULL;
	ms_init_env(ehead, env);
	ms_init_shell(ehead);
	ms_free_env(ehead);
	return (0);
}
