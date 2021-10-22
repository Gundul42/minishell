/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:22:03 by graja             #+#    #+#             */
/*   Updated: 2021/10/22 16:34:24 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* all trailing and ending whitespaces are cut of */
char	**scan_input(char *str)
{
	char	*clean;
	char	**ret;

	if (!str)
		return (NULL);
	clean = ft_strtrim(str, " \t\r\n\v\f");
	if (!clean)
		return (NULL);
	ret = ft_split(clean, ' ');
	free(clean);
	return (ret);
}
