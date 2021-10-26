/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 11:14:21 by graja             #+#    #+#             */
/*   Updated: 2021/05/27 13:46:16 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
int	ft_countdel(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

static
int	ft_getlen(char const *s, char c)
{
	int	count;

	count = 0;
	while ((*s != c) && (*s != '\0'))
	{
		s++;
		count++;
	}
	return (count);
}

static
void	ft_freemem(char **matrix, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static
int	ft_cutter(char **res, char *bck, char c)
{
	int	i;
	int	slen;

	i = 0;
	while (*bck != '\0')
	{
		slen = ft_getlen(bck, c);
		if (slen > 0)
		{
			res[i] = malloc(sizeof(char) * (slen + 1));
			if (!res[i])
			{
				ft_freemem(res, (i - 1));
				return (-1);
			}
			ft_memcpy(res[i], bck, slen);
			res[i][slen] = '\0';
			i++;
		}
		bck += slen;
		if (*bck != '\0')
			bck++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*bck;
	int		i;
	int		all;
	char	d[2];

	ft_bzero(d, 2);
	d[1] = c;
	bck = ft_strtrim(s, d);
	if (!bck)
		return (NULL);
	all = ft_countdel(bck, c) + 2;
	res = malloc(sizeof(char *) * all);
	if (res)
	{
		i = ft_cutter(res, bck, c);
		if (i >= 0)
			res[i] = NULL;
	}
	free(bck);
	return (res);
}
