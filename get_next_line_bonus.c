/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:27:55 by wweerasi          #+#    #+#             */
/*   Updated: 2024/08/02 20:57:58 by wweerasi         ###   ########.fr       */
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

	if (!**stash)
		return (NULL);
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
	int			bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || fd > _POSIX_OPEN_MAX || BUFFER_SIZE <= 0 || !buffer)
		return (ft_free(buffer));
	if (!stash[fd])
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(buffer));
		buffer[bytes_read] = '\0';
		stash[fd] = ft_strdup(buffer);
	}
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

//main to test gnl bonus function
/*
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int     fd[argc];
    char    *line;
    int        i;
    int        j;
    int        flag;

    if (argc == 1)
    {
        fd[0] = 1;
        line = get_next_line(fd[0]);
        printf("line:%s", line);
        while (line)
        {
            free(line);
            line = get_next_line(fd[0]);
            printf("line:%s", line);
        }
        if (line)
            free (line);
    }
    else
    {
        i = 1;
        while (i < argc)
        {
            fd[i - 1] = open(argv[i], O_RDONLY);
            if (fd[i - 1] == -1)
            {
                printf("Error opening file");
                return (1);
            }
            i++;
        }
        fd[i] = 0;
        i = 1;
        flag = 0;
        while (flag < argc - 1)
        {
            j = 0;
            flag = 0;
            while (fd[j])
            {
                line = get_next_line(fd[j]);
                printf("[%d] - %s", j, line);
                if (line == NULL)
                {
		       	printf("\n");
			flag++;
		}
                free(line);
                j++;
            }
            i++;
        }
        i = 1;
        while (i < argc)
        {
            close(fd[i - 1]);
            i++;
        }
    }
    return (0);
}*/
