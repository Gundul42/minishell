/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:26:28 by dmylonas          #+#    #+#             */
/*   Updated: 2021/10/27 11:46:17 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Greeting shell during startup
void	ms_init_shell(t_list **head)
{
	char	*input;
	char	*prompt;
	t_split	data;
	int		err;

	err = 0;
	while (err >= 0)
	{
		data.i = 0;
		prompt = ms_getprompt(*head);
		if (!(input = readline(prompt)))
		{
			free(prompt);
			return ;
		}
		free(prompt);
		if (ft_strlen(input))
			add_history(input);
		ms_input_parser(input, &data);
		free(input);
		err = ms_execute(head, &data);
	}
}

int main(int argc, char **argv, char **env)
{
	t_list	**ehead;
	
	ehead = malloc(sizeof(t_list));
	if (!ehead || !argc || !argv)
		return (1);
	*ehead = NULL;
	ms_init_env(ehead, env);
	ms_init_shell(ehead);
	return (0);
}
