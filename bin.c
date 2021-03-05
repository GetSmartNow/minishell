/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:50:33 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/05 16:50:37 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		mini_bin1(t_mini *s)
{
	char		**bin = NULL;
	char		*line = NULL;
	int			i = 0;
	DIR				*folder;
	struct dirent	*command;
	int				flag;

	s->tmp = NULL;
	while (ft_strncmp(s->env[i], "PATH=", 5) != 0)
		i++;
	line = ft_substr(s->env[i], 5, ft_strlen(s->env[i]));
	bin = ft_split(line, ':');
	i = 0;

	flag = 0;
	i = 0;
	printf("m|%s|\n", s->mass3d[0][0]);
	while (bin[i] && flag == 0)
	{
		folder = opendir(bin[i]);
		// if (folder == NULL)
		// {
		// 	write(1, "error\n", 6);
		// 	exit (127);
		// }
		while ((command = readdir(folder)))
		{
			if (ft_strcmp(command->d_name, s->mass3d[0][0]) == 0) //if (ft_strcmp(command->d_name, s->arg[0]) == 0)
			{
				flag = 1;
				bin[i] = ft_strjoin(bin[i], "/");
				s->var.bin = ft_strjoin(bin[i], s->mass3d[0][0]); //s->var.bin = ft_strjoin(s->var.bin, s->arg[0]);
			}
		}
		closedir(folder);
		i++;
	}
	ft_memdel_2d((void**)bin);
	return (flag);
}

int		mini_bin(t_mini *s)
{
	pid_t			pid;
	int				res = 0;
	int				status;
	char			*bin = NULL;

	res = mini_bin1(s);
	pid = fork();
	if (pid < 0)
	{
		write(1, "error\n", 6);
		exit (127);
	}
	else if (pid == 0)
	{
		execve(s->var.bin, s->mass3d[0], s->env);
		exit (1);
	}
	if (res)
		ft_memdel_1d(s->var.bin);
	if (res == 0)
	{
		write(1, "bash: ", 6);
		write(1, s->mass3d[0][0], ft_strlen(s->mass3d[0][0]));
		write(1, ": command not found\n", 20);
	}
	if (waitpid(pid, &status, 0) > 0)
		return (status);
	return (0);
}