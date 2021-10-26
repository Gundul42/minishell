/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:44:29 by graja             #+#    #+#             */
/*   Updated: 2021/05/27 14:21:25 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	alen;
	size_t	blen;
	char	*ptr;

	alen = ft_strlen(s1) + 1;
	blen = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (alen + blen + 1));
	if (!ptr)
		return (ptr);
	ft_strlcpy(ptr, s1, alen);
	ft_strlcat(ptr, s2, blen + alen + 1);
	return (ptr);
}
