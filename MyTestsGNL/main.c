/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:41:22 by wweerasi          #+#    #+#             */
/*   Updated: 2024/08/21 14:36:48 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

//empty file

int	main(void)
{
	int		fd;
	char	*line;
	static int i;

	fd = open("gnl_b3.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("line [%i] : %s\n", i++, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
