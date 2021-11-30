/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:20:13 by dmylonas          #+#    #+#             */
/*   Updated: 2021/11/29 22:22:22 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_exit_here(int fd, char *str)
{
	printf("warning: here-document delimited by");
	printf(" end-of-file (wanted \'%s\')\n", str);
	close(fd);
	exit(errno);
}
