/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 08:48:09 by graja             #+#    #+#             */
/*   Updated: 2021/09/19 18:22:07 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* We are using a special gnl_strlen here. It uses the flags 0 and 1.
 * 0 means gnl_strlen like in the definition, but calling with the flag
 * 1 means, it will count until '\n' OR '\0'.
*/

#include "gnl.h"

/* This function gets sure that *line is valid and that in case of EOF
 * the buffer[fd] is freed to prevent memory leaks.
*/

static
int	ft_check_and_free(char **line, char **ptr, int err)
{
	if (!*line)
		*line = ft_calloc(1, sizeof(char));
	if (err == 0)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (0);
}

/* This function is doing the hard copy work, it allocates the
 * right amount of memory and breaks if it fails in doing so. 
 * On success it copies and frees the old memory which is not
 * needed anymore. Using strlcat on an empty string works
 * perfectly which is proven here
*/

static
int	ft_do_copy(char **line, char *ptr, int len)
{
	char	*hlp;

	if (!*line)
	{
		*line = ft_calloc(len + 1, sizeof(char));
		if (!*line)
			return (-1);
		ft_strlcat(*line, ptr, len + 1);
	}
	else
	{
		hlp = ft_calloc(len + 1, sizeof(char));
		if (!hlp)
			return (-1);
		ft_strlcat(hlp, *line, len + 1);
		ft_strlcat(hlp, ptr, len + 1);
		free(*line);
		*line = hlp;
	}
	return (1);
}

/* this function handles the case a '\n' was found. This means not the whole
 * buffer can be copied, but only a part of it. The copied part will be removed
 * from buffer and we are ready for the next turn
*/

static
int	ft_handle_cr(char **line, char *ptr)
{
	int		len;
	int		i;

	len = gnl_strlen(ptr, 1);
	if (!*line)
		i = ft_do_copy(line, ptr, len);
	else
		i = ft_do_copy(line, ptr, gnl_strlen(*line, 0) + len);
	if (i < 0)
		return (i);
	len++;
	i = 0;
	while (ptr[len + i])
	{
		ptr[i] = ptr[len + i];
		i++;
	}
	ft_bzero((ptr + i), len);
	return (1);
}

/* easy work, no '\n' found, so copy in whole and set buffer to 0
 * after work is done buffer is filled with zeros because in the
 * case of next read EOF is reached, maybe not the whole BUFFER_SIZE
 * would be read and so it could contain old information in it's tail.
*/

static
int	ft_copy_content(char **line, char *ptr)
{
	int	err;
	int	len;

	len = gnl_strlen(ptr, 0);
	if (!*line)
		err = ft_do_copy(line, ptr, len);
	else
		err = ft_do_copy(line, ptr, len + gnl_strlen(*line, 0));
	if (err > 0)
		ft_bzero(ptr, len);
	return (err);
}

/* What was asked for. The only difference between this and the bonus part
 * is the size of the array to handle the different fds.
 * Calloc is used to make sure that every string is NULL terminated. As long
 * as no '\n' is found it will add buffer to the string which will be returned,
 * finally adding the last part until the '\n' and keeping the remains in the
 * buffer the static variable is pointing to.
*/

int	get_next_line(int fd, char **line)
{
	int			err;
	static char	*buffer[1024];

	err = 1;
	if (read(fd, NULL, 0) < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer[fd])
		return (-1);
	if (*line)
		*line = NULL;
	if (gnl_strlen(buffer[fd], 0) == 0)
		err = read(fd, buffer[fd], BUFFER_SIZE);
	while (err > 0 && !(ft_strchr(buffer[fd], '\n')))
	{
		err = ft_copy_content(line, buffer[fd]);
		if (err > 0)
			err = read(fd, buffer[fd], BUFFER_SIZE);
	}
	if (err > 0)
		err = ft_handle_cr(line, buffer[fd]);
	ft_check_and_free(line, &buffer[fd], err);
	return (err);
}
