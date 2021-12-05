/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:38:30 by dmylonas          #+#    #+#             */
/*   Updated: 2021/12/05 12:10:00 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* 'int num' does not make sense
 * it is there solely to make
 * norminette shut up
 */
//ctrl + C when interactive
static
void	display_prompt(int num)
{	
	num++;
	g_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* redirecting SIGINT to a new prompt
 * and cancelling SIGQUIT
 */
void	define_input_signals(void)
{
	signal(SIGINT, display_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	interrupt_here_document(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(errno);
}
