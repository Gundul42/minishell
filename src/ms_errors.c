/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:22:52 by graja             #+#    #+#             */
/*   Updated: 2021/12/05 12:00:43 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// int	ms_print_error(t_list **head, const char *str, int nbr)
// {
// 	char	*name;
// 	if (str)
// 		perror(str);
// 	if (nbr < 0)
// 		nbr = EXIT_FAILURE;
// 	name = ft_itoa(nbr);
// 	ms_putenv(head, "?", name);
// 	free(name);
// 	return (nbr);
// }
void	ms_print_error_for_glob(const char *str, int nbr)
{
	if (str)
		perror(str);
	if (nbr < 0)
		nbr = EXIT_FAILURE;
	g_status = nbr;
}

// void	ms_c_error(t_list **head, char *s1, char *s2, int nbr)
// {
// 	char	*msg;
// 	msg = ft_calloc(ft_strlen(s1) + ft_strlen(s2) +1, sizeof(char));
// 	if (!msg)
// 		return ;
// 	ft_strlcat(msg, s1, ft_strlen(s1) + 1);
// 	ft_strlcat(msg, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
// 	ft_putendl_fd(msg, STDERR_FILENO);
// 	free(msg);
// 	msg = ft_itoa(nbr);
// 	ms_putenv(head, "?", msg);
// 	free(msg);
// }
void	ms_c_error_for_glob(char *s1, char *s2, int nbr)
{
	char	*msg;

	msg = ft_calloc(ft_strlen(s1) + ft_strlen(s2) +1, sizeof(char));
	if (!msg)
		return ;
	ft_strlcat(msg, s1, ft_strlen(s1) + 1);
	ft_strlcat(msg, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	g_status = nbr;
}
