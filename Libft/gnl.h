/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:55:44 by graja             #+#    #+#             */
/*   Updated: 2021/09/19 18:21:49 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# include "libft.h"
# include "gnl.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

size_t	gnl_strlen(const char *s, int flag);
int		get_next_line(int fd, char **line);

#endif
