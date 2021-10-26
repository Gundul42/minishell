/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:26:28 by dmylonas          #+#    #+#             */
/*   Updated: 2021/10/26 12:18:03 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Greeting shell during startup
void	ms_init_shell(t_list **head)
{
	char	*input;
	char	*prompt;
	t_split	data;

	while (1)
	{
		data.i = 0;
		prompt = ms_getprompt(*head);
		if (!(input = readline(prompt)))
		{
			free(prompt);
			return ;
		}
		free(prompt);
		/* printf("the input is: %s\n", input);
		 * only add to history if strlen > 0
		 */
		if (ft_strlen(input))
			add_history(input);
		ms_input_parser(input, &data);
		int j = -1;
		while (j++ < 7)
		{
			printf("argument %d is: %s\n", j, data.tokens[j]);
		}
	}
}

int main(int argc, char **argv, char **env)
{
	t_list	**ehead;
	
	ehead = malloc(sizeof(t_list));
	if (!ehead || !argc || !argv)
		return (1);
	ms_init_env(ehead, env);
	ms_init_shell(ehead);
	return (0);

}
