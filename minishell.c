/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:32:52 by graja             #+#    #+#             */
/*   Updated: 2021/10/19 15:15:44 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	main(int argc, char **argv)
{
	char	*line;

	line = readline(">> ");
	while (line)
	{
		printf("[%s]\n", line);
		if (ft_strlen(line) > 0)
			add_history(line);
		free(line);
		line = readline(">> ");
	}
	printf("\n%d) Len = %ld\n", argc, ft_strlen(argv[0]));
	return (0);
}
