/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:27:55 by wweerasi          #+#    #+#             */
/*   Updated: 2024/08/01 20:52:21 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char *s)
{
	free(s);
	s = NULL;
	return (s);
}

static char	*l_construct(char **stash)
{
	char	*line;
	char	*res;
	char	*l_end;

	line = NULL;
	if (**stash)
	{
		l_end = ft_strchr(*stash, '\n');
		if (l_end)
		{
			line = ft_substr(*stash, 0, (l_end - *stash + 1));
			res = ft_strdup(ft_strchr(*stash, '\n') + 1);
			ft_free(*stash);
			*stash = ft_strdup(res);
			ft_free(res);
		}
		else
		{
			line = ft_strdup(*stash);
			ft_free(*stash);
			*stash = NULL;
		}
	}
	return (line);
}

static char	*l_read(int fd, char *buf, char **stash)
{
	char	*tmp_stash;
	char	*line;
	int	bytes_read;

	line = NULL;
	while (!ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(*stash));
		buf[bytes_read] = '\0';
		tmp_stash = *stash;
		*stash = ft_strjoin(tmp_stash, buf);
		ft_free(tmp_stash);
		if (!stash)
			return (ft_free(*stash));
		if (bytes_read < BUFFER_SIZE)
			break ;
	}
	line = l_construct(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[_POSIX_OPEN_MAX];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!stash[fd])
	{
		stash[fd] = ft_strdup("");
		if (!stash[fd])
			return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = l_read(fd, buffer, &stash[fd]);
	ft_free(buffer);
	if (!line)
	{
		line = ft_free(line);
		if (!stash[fd])
			return (ft_free(stash[fd]));
	}
	return (line);
}
