/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:15:39 by graja             #+#    #+#             */
/*   Updated: 2021/11/10 12:43:13 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static
char	*make_pname(char *name, char *path)
{
	char	*fnd;

	fnd = calloc(ft_strlen(path) + ft_strlen(name) + 2, sizeof(char));
	if (!fnd)
		return (NULL);
	ft_strlcat(fnd, path, ft_strlen(path) + 1);
	ft_strlcat(fnd, "/", ft_strlen(fnd) + 2);
	ft_strlcat(fnd, name, ft_strlen(fnd) + ft_strlen(name) + 1);
	return (fnd);
}

static
int	check_file(char *name, int flag)
{
	struct stat	buf;

	if (flag)
		return (flag);
	if (name && !stat(name, &buf))
		return (1);
	if (name)
		free(name);
	return (0);
}

static
char	*check_name(char *name)
{
	struct stat	buf;
	char		*back;

	if (!ft_strchr(name, '/'))
		return (NULL);
	if (stat(name, &buf) < 0)
		return (NULL);
	back = calloc(ft_strlen(name) + 1, sizeof(char));
	if (!back)
		return (NULL);
	back = ft_memcpy(back, name, ft_strlen(name));
	return (back);
}

char	*ms_file_exists(char *name, char *path, int i)
{
	char	**srch;
	char	*fnd;
	int		fflag;

	fflag = 0;
	if (!path || !name)
		return (NULL);
	fnd = check_name(name);
	if (fnd)
		return (fnd);
	srch = ft_split(path, ':');
	while (srch[i])
	{
		if (!fflag && !ft_strchr(name, '/'))
			fnd = make_pname(name, srch[i]);
		fflag = check_file(fnd, fflag);
		free(srch[i]);
		i++;
	}
	free(srch);
	if (fflag)
		return (fnd);
	else
		return (NULL);
}
