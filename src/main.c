/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:26:28 by dmylonas          #+#    #+#             */
/*   Updated: 2021/12/03 15:37:59 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
void	ms_init_shell(t_list **head, t_list **lsthead, char *input, char *prt)
{
	while (1)
	{
		prt = ms_getprompt(*head);
		define_input_signals();
		input = readline(prt);
		if (!input)
		{
			free(prt);
			ms_exit(head, lsthead);
		}
		free(prt);
		if (!ft_strlen(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		scan_input(input, head, lsthead);
		if (!ms_read_arguments(lsthead, 0, 0))
			ms_execute(head, lsthead);
		else
			ms_c_error(head, "syntax ", " error", 2);
	}
}

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
	ms_init_shell(ehead, lsthead, NULL, NULL);
	return (0);
}
