/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:10:50 by dmylonas          #+#    #+#             */
/*   Updated: 2021/12/01 01:12:00 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
void	display_for_blocking_cmd(int num)
{
	num++;
	g_status = 130;
	write(1, "\n", 1);
}

static
void	quit_process(int num)
{
	num++;
	g_status = 131;
	printf("Quit (core dumped)\n");
}

void	signal_for_blocking_cmd(void)
{
	signal(SIGINT, display_for_blocking_cmd);
	signal(SIGQUIT, quit_process);
}
