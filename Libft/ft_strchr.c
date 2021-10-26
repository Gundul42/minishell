/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:05:36 by graja             #+#    #+#             */
/*   Updated: 2021/05/27 14:15:36 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*bck;

	bck = (char *)s;
	while (*bck)
	{
		if (*bck == (char)c)
			return (bck);
		bck++;
	}
	if (!(*bck) && !c)
		return (bck);
	else
		return (NULL);
}
