/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:52:00 by graja             #+#    #+#             */
/*   Updated: 2021/10/26 13:06:46 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_builtin_cd(t_list **head, t_split *data)
{
	printf("*] cd    ....\n");
	if (!head || !data)
		return (1);
	return (0);
}
