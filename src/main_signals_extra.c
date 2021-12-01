/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:10:50 by dmylonas          #+#    #+#             */
/*   Updated: 2021/12/01 11:21:36 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
void	display_for_blocking_cmd(int num)
{
	num++;
	g_ms_sigerr = 130;
	write(STDERR_FILENO, "\n", 1);
}

static
void	quit_process(int num)
{
	num++;
	g_ms_sigerr = 131;
	ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
}

void	signal_for_blocking_cmd(void)
{
	signal(SIGINT, display_for_blocking_cmd);
	signal(SIGQUIT, quit_process);
}
