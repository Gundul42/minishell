/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:50:05 by graja             #+#    #+#             */
/*   Updated: 2021/12/01 01:04:38 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_builtin_pwd(t_list **head)
{
	char	*str;

	str = ms_getenv(*head, "PWD");
	if (str)
		printf("%s\n", str);
	// ms_print_error(head, NULL, 0);
	ms_print_error_for_glob(NULL, 0);
}
