/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:15:44 by graja             #+#    #+#             */
/*   Updated: 2021/05/28 10:48:22 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
void	ft_printit(int n, int fd)
{
	int	h;

	if (n > 0)
	{
		h = 48 + (n % 10);
		n /= 10;
		ft_printit(n, fd);
		ft_putchar_fd(h, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
		ft_printit(n, fd);
	}
	else if (n > 0)
		ft_printit(n, fd);
	else if (n == 0)
		ft_putchar_fd('0', fd);
}
