/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouahib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:00:45 by aouahib           #+#    #+#             */
/*   Updated: 2019/10/28 20:12:32 by aouahib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	extract_line(char **line, char *buf, char *new_line)
{
	int size;

	size = new_line - buf + 1;
	*line = malloc(size);
	if (!line)
		return (-1);
	ft_strlcpy(*line, buf, size);
	ft_strlcpy(buf, new_line + 1, ft_strlen(buf) + 1);
	return (1);
}

int	read_to_buf(int fd, char **buf)
{
	char	*tmp_buf;
	char	*tmp;
	int		size;

	tmp_buf = malloc(BUFFER_SIZE + 1);
	if (!tmp_buf)
		return (-1);
	size = read(fd, tmp_buf, BUFFER_SIZE);
	if (size > 0)
	{
		tmp_buf[size] = 0;
		tmp = *buf;
		*buf = ft_strjoin(*buf, tmp_buf);
		free(tmp);
		free(tmp_buf);
		if (!*buf)
			return (-1);
	}
	else
		free(tmp_buf);
	return (size);
}

int	get_next_line(int fd, char **line)
{
	static char	*bufs[500];
	char		*new_line;
	int			res;

	if (fd < 0 || fd > 499)
		return (-1);
	new_line = ft_strchr(bufs[fd], '\n');
	if (new_line)
		return (extract_line(line, bufs[fd], new_line));
	res = read_to_buf(fd, &bufs[fd]);
	if (res > 0)
		return (get_next_line(fd, line));
	if (!res)
	{
		*line = bufs[fd][0] ? ft_strdup(bufs[fd]) : 0;
		free(bufs[fd]);
		bufs[fd] = 0;
		if (!*line)
			return (-1);
		return (ft_strlen(*line) > 0);
	}
	free(bufs[fd]);
	bufs[fd] = 0;
	return (-1);
}
