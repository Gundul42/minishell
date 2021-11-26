/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_here_doc_signal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 00:38:15 by dmylonas          #+#    #+#             */
/*   Updated: 2021/11/07 00:38:16 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_here_document(int signal)
{
	(void)signal;
	g_minishell.error_status = 130;
	write(1, "\n", 1);
	exit(130);
}
