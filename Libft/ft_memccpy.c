/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:16:24 by graja             #+#    #+#             */
/*   Updated: 2021/05/20 18:04:06 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char			*d;
	char			*s;
	unsigned int	i;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while ((i < n) && (*s != (char)c))
	{
		*d = *s;
		s++;
		d++;
		i++;
	}
	if (*s == (char)c)
	{
		*d = *s;
		d++;
		return (d);
	}
	else
		return (NULL);
}
