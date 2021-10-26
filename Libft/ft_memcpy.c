/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:25:07 by graja             #+#    #+#             */
/*   Updated: 2021/05/20 18:06:25 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*tgt;
	char			*ptr;

	tgt = (char *)dest;
	ptr = (char *)src;
	i = 0;
	while (i < n)
	{
		tgt[i] = ptr[i];
		i++;
	}
	return (dest);
}
