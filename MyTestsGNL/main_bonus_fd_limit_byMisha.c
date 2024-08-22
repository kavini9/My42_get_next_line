/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus_fd_limit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:04:02 by wweerasi          #+#    #+#             */
/*   Updated: 2024/08/21 16:14:30 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
int main()
{
	char *line;
	int fds[FD_MAX];
	int i = 3;
	
	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;
//	char *some;	
	while(i < FD_MAX + 5)
	{
		if (i < FD_MAX - 5)
			fds[i] = open("some", O_RDONLY);
		else
			fds[i] = i;
		printf("opened %d\n", fds[i]);
		i++;
	}
	i = 0;
	while (i < FD_MAX + 5)
	{	
		if (i == 1)
		{
			i++;
			i++;
		}
		printf("%d fds[i]: %d\n", i, fds[i]);
		if (fds[i] > -1)
		{
			while(line)
			{
				line = get_next_line(fds[i]);
				if (line)
				{
					printf("%s", line);
					free(line);
				}
			}
//			line = some;
			if (i != 0)
				close(fds[i]);
		} else
		{
			printf("opening error, i: %d fds[i]: %d\n", i, fds[i]);
		}
		i++;
	}
	return (0);
}
