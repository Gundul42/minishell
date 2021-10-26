/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:29:01 by graja             #+#    #+#             */
/*   Updated: 2021/09/19 18:22:25 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

size_t	gnl_strlen(const char *s, int flag)
{
	size_t	i;

	i = 0;
	if (flag <= 0)
	{
		while (s[i] != '\0')
			i++;
	}
	else
		while (s[i] != '\0' && s[i] != '\n')
			i++;
	return (i);
}
