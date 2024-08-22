/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:04:55 by wweerasi          #+#    #+#             */
/*   Updated: 2024/08/22 16:57:03 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int     fd[argc -  1];
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
}
