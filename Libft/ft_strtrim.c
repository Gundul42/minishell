/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:21:14 by graja             #+#    #+#             */
/*   Updated: 2021/05/27 13:57:27 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
int	ft_checkchr(char c, char const *pool)
{
	int	i;

	i = 0;
	while (pool[i])
	{
		if (pool[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	int		j;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (ft_checkchr(s1[i], set))
		i++;
	while ((i != len) && (ft_checkchr(s1[len - 1], set)))
		len--;
	len = len - i;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	j = 0;
	while (j < len)
	{
		ptr[j] = s1[i + j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
