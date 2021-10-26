/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 15:48:02 by graja             #+#    #+#             */
/*   Updated: 2021/05/22 14:05:03 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	l;
	size_t	i;
	size_t	len;

	l = 0;
	i = 0;
	len = ft_strlen(dst);
	if (dstsize == 0 || (len > dstsize - 1))
		return (ft_strlen(src) + dstsize);
	l = len;
	while (((len + i) < (dstsize - 1)) && (src[i]))
	{
		dst[l] = src[i];
		l++;
		i++;
	}
	dst[l] = '\0';
	if (len >= dstsize)
		len = dstsize;
	return (len + ft_strlen(src));
}
