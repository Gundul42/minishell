/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:09:29 by graja             #+#    #+#             */
/*   Updated: 2021/05/27 14:17:47 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*bck;
	char	*ret;

	ret = NULL;
	bck = (char *)s;
	while (*bck)
	{
		if (*bck == c)
			ret = bck;
		bck++;
	}
	if (!(*bck) && !c)
		ret = bck;
	return (ret);
}
