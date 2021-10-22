/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:32:52 by graja             #+#    #+#             */
/*   Updated: 2021/10/22 16:54:35 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
void	ft_printit(char *line)
{
	char	**str;
	int		i;

	i = 0;
	if (!line)
		return ;
	str = scan_input(line);
	parse(str);
	while (str && str[i])
	{
		printf("[%s]\n", str[i]);
		free(str[i]);
		i++;
	}
	free(str);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*dname;

	dname = ft_strjoin(getcwd(NULL, 0),"$ ");
	line = readline(dname);
	while (line)
	{
		if (ft_strlen(line) > 0)
			add_history(line);
		ft_printit(line);
		free(line);
		line = readline(dname);
	}
	printf("\n%d) Len = %ld\n", argc, ft_strlen(argv[0]));
	free(dname);
	return (0);
}
