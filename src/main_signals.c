/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:38:30 by dmylonas          #+#    #+#             */
/*   Updated: 2021/11/20 14:52:59 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* 'int num' does not make sense
 * it is there solely to make
 * norminette shut up
 */
static
void	display_prompt(int num)
{	
	num++;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
/*	g_minishell.error_status = 130;*/
}

/* redirecting SIGINT to a new prompt
 * and cancelling SIGQUIT
 */
void	define_input_signals(void)
{
	signal(SIGINT, display_prompt);
	signal(SIGQUIT, SIG_IGN);
}
