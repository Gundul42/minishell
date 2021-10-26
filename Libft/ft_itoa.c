/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:20:24 by graja             #+#    #+#             */
/*   Updated: 2021/05/27 14:12:04 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
int	ft_getlen(long long n, int len)
{
	if (n < 0)
	{
		n *= -1;
		len = 1;
	}
	if (n < 10)
		len++;
	else
	{
		len++;
		len = ft_getlen((n / 10), len);
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	long long	x;
	char		*str;

	x = n;
	len = ft_getlen(x, 0);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (str);
	str[len] = 0;
	if (x < 0)
		x *= -1;
	while (len > 0)
	{
		str[len - 1] = 48 + (x % 10);
		x /= 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
