/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:05:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/22 14:12:54 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		init_pipes(t_mini *s)
{
	int			i = -1;
	
	s->pipe.fd = (int **)malloc(sizeof(int *) * s->pipe.count_pipe);
	while (++i < s->pipe.count_pipe)
	{
		s->pipe.fd[i] = (int *)malloc(sizeof(int) * 2);
	}
	i = -1;
	while (++i < s->pipe.count_pipe)
	{
		pipe(s->pipe.fd[i]);
	}
	return (0);
}

static int		mini_bin1(t_mini *s, int i)
{
	char		**bin = NULL;
	char		*line = NULL;
	t_mass		*tmp;
	int			m = 0;
	DIR				*folder;
	struct dirent	*command;
	int				flag;

	flag = 0;
	tmp = s->head;
	while (tmp != NULL && ft_strncmp(tmp->content, "PATH=", 5) != 0)
		tmp = tmp->next;
	if (s->mass3d[i][0][0] == '/')
		s->var.bin = ft_strdup(s->mass3d[i][0]);
	else if (tmp == NULL)
		return (-1);
	else
	{
		line = ft_substr(tmp->content, 5, ft_strlen(tmp->content));
		bin = ft_split(line, ':');
		ft_memdel_1d(line);
		m = 0;
		while (bin[m] && flag == 0) //bin[m + 3]
		{
			// printf("%s\n", bin[m]);
			folder = opendir(bin[m]);
			if (folder == NULL)
			{
				write(1, "error\n", 6);
				exit (127);
			}
			while ((command = readdir(folder)))
			{
				if (ft_strcmp(command->d_name, s->mass3d[i][0]) == 0)
				{
					flag = 1;
					line = ft_strjoin(bin[m], "/");
					s->var.bin = ft_strjoin(line, s->mass3d[i][0]);
					ft_memdel_1d(line);
				}
			}
			closedir(folder);
			m++;
		}
	}
	ft_memdel_2d((void**)bin);
	return (flag);
}

int					mini_pipes(t_mini *s) //ps -a | cat -e | cat -e
{
	int		i = 0;
	int		res;
	int		j;

	init_pipes(s);
	for(i = 0; i < s->pipe.count_commands; i++)
	{
		res = mini_bin1(s, i);
		g_sig.pid = fork();
		if (g_sig.pid == 0)
		{
			// printf("fd2: %d\n", s->array_fdout[i]);
			// printf("sdin: %d\n", s->array_fdin[i]);
			if (i == 0) // first
			{
				if (s->array_fdin[i])
				{
					dup2(s->array_fdin[i], STDIN);
					close(s->array_fdin[i]);
				}
				if (s->array_fdout[i] > 1)
				{
					dup2(s->array_fdout[i], STDOUT);
					close(s->array_fdout[i]);	
				}
				else
					dup2(s->pipe.fd[i][1], STDOUT);
				for (int k = 0; k < s->pipe.count_pipe; k++)
				{
					close(s->pipe.fd[k][1]);
					if (k != 0)
						close(s->pipe.fd[k][0]);
				}
			}
			else
			{
				if (s->array_fdin[i])
				{
					dup2(s->array_fdin[i], STDIN);
					close(s->array_fdin[i]);
				}
				else
					dup2(s->pipe.fd[i - 1][0], STDIN);
				if (s->array_fdout[i] > 1)
				{
					dup2(s->array_fdout[i], STDOUT);
					close(s->array_fdout[i]);	
				}
				else if (i + 1 != s->pipe.count_commands)
					dup2(s->pipe.fd[i][1], STDOUT);
				for (int k = 0; k < s->pipe.count_pipe; k++)
				{
					close(s->pipe.fd[k][1]);
					if (k != 0 && i + 1 != s->pipe.count_commands)
						close(s->pipe.fd[k][0]);
				}
			}
			execve(s->var.bin, s->mass3d[i], s->env);
			exit (1);
		}
		if (res)
			ft_memdel_1d(s->var.bin);
	}
	j = -1;
	while (++j < s->pipe.count_pipe)
	{
		close(s->pipe.fd[j][0]);
		close(s->pipe.fd[j][1]);
		free(s->pipe.fd[j]);
	}
	for (int i = 0; i < s->pipe.count_commands; i++)
		wait(NULL);
	free(s->pipe.fd);
	s->pipe.fd = NULL;
	return (0);
}