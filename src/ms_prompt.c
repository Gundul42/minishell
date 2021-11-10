/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:16:35 by graja             #+#    #+#             */
/*   Updated: 2021/11/10 13:25:26 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ms_getprompt(t_list *head)
{
	char	*prompt;
	char	*name;
	char	*dir;

	name = ms_getenv(head, "LOGNAME");
	dir = ms_getenv(head, "PWD");
	prompt = calloc(ft_strlen(name) + ft_strlen(dir) + 16, sizeof(char));
	ft_strlcat(prompt, name, ft_strlen(name) + 1);
	ft_strlcat(prompt, ":\033[1;34m", ft_strlen(prompt) + 9);
	ft_strlcat(prompt, dir, ft_strlen(prompt) + ft_strlen(dir) + 1);
	ft_strlcat(prompt, "\x1b[0m$ ", ft_strlen(prompt) + 8);
	return (prompt);
}
