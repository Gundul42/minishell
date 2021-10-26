/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:25:56 by graja             #+#    #+#             */
/*   Updated: 2021/05/22 08:59:25 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if ((unsigned int)(d - s) >= n)
		d = ft_memcpy(d, s, n);
	else
	{
		n--;
		d += n;
		s += n;
		while (n > 0)
		{	
			*d = *s;
			d--;
			s--;
			n--;
		}
		*d = *s;
	}
	return (d);
}
