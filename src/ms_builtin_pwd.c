/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:50:05 by graja             #+#    #+#             */
/*   Updated: 2021/10/27 11:54:02 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_builtin_pwd(t_list **head)
{
	char	*str;

	str = ms_getenv(*head, "PWD");
	if (str)
		printf("%s\n", str);
}
