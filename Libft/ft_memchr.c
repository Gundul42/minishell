/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:17:42 by graja             #+#    #+#             */
/*   Updated: 2021/05/20 19:04:14 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*bck;
	unsigned int	i;

	i = 0;
	bck = (unsigned char *)s;
	while (i < n)
	{
		if (*bck == (unsigned char)c)
		{
			return (bck);
		}
		bck++;
		i++;
	}
	return (NULL);
}
