/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:05:58 by wweerasi          #+#    #+#             */
/*   Updated: 2024/08/01 20:59:28 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	int	bytes_read;
	char	*tmp_stash;
	char	*line;

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
	static char	*stash;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = l_read(fd, buffer, &stash);
	ft_free(buffer);
	if (!line)
	{
		line = ft_free(line);
		if (!stash)
			return (ft_free(stash));
	}
	return (line);
}

//main to test GNL function
/*
int main()
{
	int fd;
	char *line;
	static int i;
	
	line = ft_strdup("");
	fd = open("ISF.txt", O_RDONLY);
	while (i < 30)
	{
		line = get_next_line(fd);
		printf("line [%i] : %s", i++, line);
		free(line);
	}
}*/
