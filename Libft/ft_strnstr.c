/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:04:38 by graja             #+#    #+#             */
/*   Updated: 2021/05/28 09:49:59 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* important to understand ! When searching for the string little this
 * function will stop searching after len chars in big. This means that
 * the string little can still be in big, only not in the first len chars
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big || !little)
		return (NULL);
	if (!little[0])
		return ((char *)big);
	i = 0;
	while (big[i] && (i < len))
	{
		j = 0;
		while ((little[j] && big[i + j] && (i + j < len)
				&& (little[j] == big[i + j])))
			j++;
		if (!little[j])
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
