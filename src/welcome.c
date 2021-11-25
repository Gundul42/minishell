/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:14:56 by graja             #+#    #+#             */
/*   Updated: 2021/11/25 15:39:24 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_welcome(void)
{
	int		fd;
	char	*str;

	fd = open("src/.welcome.txt", O_RDONLY, 0600);
	str = NULL;
	if (fd < 0)
		return ;
	while (get_next_line(fd, &str) > 0)
	{
		printf("%s\n", str);
		free(str);
	}
	if (str)
		free(str);
	close (fd);
}
