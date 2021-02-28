/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:10:51 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/28 20:25:54 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

int			main(int ac, char **av)
{
	int		fd[2];
	int		id;
	int		status;
	int		sum = 0;
	
	
	// for (int i = 0; i < 2; i++)
	// {
		pipe(fd);
		// dup2(fd[1], 1);
		// close(fd[1]);
		id = fork();
		if (id == 0) {
			close(fd[1]);
			read(fd[0], &sum, sizeof(sum));
			sum += 5;
			// printf("child sum: %d\n", sum);
		}
		else {
			close(fd[0]);
			sum += 5;
			// printf("parent sum: %d\n", sum);
			write(fd[1], &sum, sizeof(sum));
		}
		wait(NULL); 
	// }
	// if (waitpid(id, &status, 0) > 0)
	// 	return (status);
}
