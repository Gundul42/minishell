/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:26:28 by dmylonas          #+#    #+#             */
/*   Updated: 2021/11/26 07:21:28 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
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

void	ms_debug(t_list **head)
{
	t_split	*ctt;
	t_list *run;

	run = *head;
	while (run)
	{
		ctt = (t_split *)(run->content);
		printf("Iname	:%s\n", ctt->iname);
		printf("Oname	:%s\n", ctt->oname);
		printf("err	:%d\n",	ctt->err);
		printf("redi	:%d\n", ctt->redi);
		printf("redo	:%d\n", ctt->redo);
		printf("appi	:%d\n", ctt->appi);
		printf("appo	:%d\n", ctt->appo);
		printf("fdout	:%d\n", ctt->fdout);
		printf("fdin	:%d\n", ctt->fdin);
		printf("pcpyin	:%d\n", ctt->pcpyin);
		printf("pcpyout	:%d\n", ctt->pcpyout);
		printf("piped	:%d\n", ctt->piped);
		printf("pipenbr	:%d\n", ctt->pipenbr);
		printf("pipefd	:%p\n", ctt->pipefd);
		run = run->next;
	}
}

void	ms_init_shell(t_list **head, t_list **lsthead)
{
	char	*input;
	char	*prompt;
	int		err;

	err = 0;
	while (err >= 0)
	{
		prompt = ms_getprompt(*head);
		define_input_signals();
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
	ms_welcome();
	ms_init_env(ehead, environ);
	ms_putenv(ehead, "?", "0");
	ms_init_shell(ehead, lsthead);
	ms_free_env(ehead, 0);
	ms_free_env(lsthead, 1);
	return (0);
}
