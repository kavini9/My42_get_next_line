/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:05:58 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/29 20:08:48 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

char	*ft_free(char *s)
{
	free(s);
	s = NULL;
	return (s);
}
//static char *l_construct
static char *l_read(int fd, char *buf, char **stash)
{
    int     bytes_read;
    char    *tmp_stash;
    char    *line;
	char	*res;

    bytes_read = BUFFER_SIZE;
    while(!ft_strchr(*stash, '\n'))
    {
        bytes_read = read(fd, buf, BUFFER_SIZE);
        if (bytes_read == -1)
            return (ft_free(*stash));
        if (bytes_read == 0)
            break;
        buf[bytes_read] = '\0';
		tmp_stash = *stash;
        *stash = ft_strjoin(tmp_stash, buf);// shouldn't I check if this exist
        ft_free(tmp_stash);
	}
	line = ft_substr(*stash, 0, (ft_strchr(*stash,'\n') - *stash  + 2));
	if (line)
		res = ft_strdup(ft_strchr(*stash, '\n') + 1);
	else 
		return (ft_free(*stash));
	*stash = ft_strdup(res);
   	ft_free(res);
	return(line);
}

char *get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || read(fd, NULL, 0) < 0)
        return (NULL);
    if (!stash)
        stash = ft_strdup("");
	if (!stash)
		return (NULL);
    line = l_read(fd, buffer, &stash);
    if (!line)
        line = ft_free(line);
    return (line);
}


/*
int main(void)
{
	char *s1;
	char *s2 = "abc";
	char *j;

	j = ft_strjoin(s1, s2);
	printf("ft_strjoin: %s\n", j);
	free(j);
}*/
/*
int main(void)
{
	int	fd;
	int		bytes_read;
	char		buf[BUFFER_SIZE + 1];

	fd = open("Empty.txt", O_RDONLY);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	printf("Buffer: -%s-, Bytes_read: %i\n", buf, bytes_read);
}*/
/*
int main()
{
	int fd;
	char *line;
	static int i;
	
	line = ft_strdup("");
	fd = open("ISF.txt", O_RDONLY);
	while (line)
	{
		line = get_next_line(fd);
		printf("line [%i] : %s", i++, line);
	}
}*/


