/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:16:35 by graja             #+#    #+#             */
/*   Updated: 2021/10/26 12:19:36 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ms_getprompt(t_list *head)
{
	char	*prompt;

	prompt = ft_strjoin(ms_getenv(head, "LOGNAME"), ":\033[1;34m");
	prompt = ft_strjoin(prompt, ms_getenv(head, "PWD"));
	prompt = ft_strjoin(prompt, "\x1b[0m$ ");
	return (prompt);
}
