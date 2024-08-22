/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:27:55 by wweerasi          #+#    #+#             */
/*   Updated: 2024/08/22 21:42:37 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char **s)
{
	free(*s);
	*s = NULL;
	return (*s);
}

static char	*l_construct(char **stash)
{
	char	*line;
	char	*res;
	char	*l_end;

	if (!**stash)
		return (NULL);
	l_end = ft_strchr(*stash, '\n');
	if (l_end)
	{
		line = ft_substr(*stash, 0, (l_end - *stash + 1));
		if (!line)
			return (NULL);
		res = ft_strdup(l_end + 1);
		if (!res)
			return (ft_free(&line));
		ft_free(stash);
		*stash = ft_strdup(res);
		ft_free(&res);
		if (!*stash)
			return (ft_free(&line));
		return (line);
	}
	line = ft_strdup(*stash);
	ft_free(stash);
	return (line);
}

static char	*l_read(int fd, char *buf, char **stash)
{
	char	*tmp_stash;
	char	*line;
	int		bytes_read;

	line = NULL;
	while (!ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(stash));
		buf[bytes_read] = '\0';
		tmp_stash = *stash;
		*stash = ft_strjoin(tmp_stash, buf);
		ft_free(&tmp_stash);
		if (!*stash)
			return (ft_free(stash));
		if (bytes_read < BUFFER_SIZE)
			break ;
	}
	line = l_construct(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX + 1];
	char		*buffer;
	char		*line;
	int			bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0 || !buffer)
		return (ft_free(&buffer));
	if (!stash[fd])
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(&buffer));
		buffer[bytes_read] = '\0';
		stash[fd] = ft_strdup(buffer);
		if (!stash[fd])
			return (ft_free(&buffer));
	}
	line = l_read(fd, buffer, &stash[fd]);
	ft_free(&buffer);
	if (!line)
		ft_free(&stash[fd]);
	return (line);
}
