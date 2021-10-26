/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:10:14 by graja             #+#    #+#             */
/*   Updated: 2021/05/27 14:07:55 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
int	ft_space(char c)
{
	if (((c >= 8) && (c <= 13)) || (c == 32))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int			sign;
	int			res;

	res = 0;
	sign = 1;
	while (ft_space(*nptr))
		nptr++;
	if ((*nptr == '-') || (*nptr == '+'))
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		res *= 10;
		res += (*nptr - 48);
		nptr++;
	}
	res *= sign;
	return (res);
}
