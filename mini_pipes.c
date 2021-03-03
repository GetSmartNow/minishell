/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:05:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/03 18:10:01 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			ft_list_to_2d(t_mini *s)
{
	t_mass			*tmp;
	int				i = 0;

	tmp = s->head;
	while (tmp != NULL)
	{
		s->env[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	while (s->env[i])
	{
		s->env[i] = NULL;
		i++;
	}
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
	{
		tmp = tmp->next;
	}
	if (s->mass3d[i][0][0] == '/')
	{
		s->var.bin = ft_strdup(s->mass3d[i][0]);
	}
	else if (tmp == NULL)
		return (-1);
	else if (ft_strncmp(s->mass3d[i][0], "minishell", 9) == 0 || \
			ft_strncmp(s->mass3d[i][0], "./minishell", 11) == 0)
	{
		s->var.bin = ft_strdup("minishell");
		ft_list_to_2d(s);
	}
	else
	{
		line = ft_substr(tmp->content, 5, ft_strlen(tmp->content));
		bin = ft_split(line, ':');
		ft_memdel_1d(line);
		m = 0;
		while (bin[m] && flag == 0)
		{
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
	int		fd[s->pipe.count_commands - 1][2];
	// int		**fd;
	int		tmpin = 0;
	int		tmpout = 0;
	int		fdin = 0;
	int		fdout = 0;
	int		i = 0;
	int				status;
	int		res;
	pid_t	id;
	int		j;

	// fd = (int **)malloc(sizeof(int *) * s->pipe.count_pipe);
	// while (fd[i])
	// {
	// 	fd[i] = (int *)malloc(sizeof(int) * 2);
	// 	i++;
	// }
	// printf("|%d|\n", s->pipe.count_commands);
	for(i = 0; i < s->pipe.count_commands; i++) // ls | cat -e | cat -e
	{
		res = mini_bin1(s, i);
		pipe(fd[i]);
		id = fork();
		if (id == 0)
		{
			if (i == 0) // first
			{
				// for (int k = 0; k <= i; k++)
				// {
				// 	if (k != 0)
				// 		close(fd[k][1]);
				// 	close(fd[k][0]);
				// }
				close(fd[i][0]);
				dup2(fd[i][1], STDOUT);
				close(fd[i][1]);
			}
			else
			{
				close(fd[i - 1][1]);
				dup2(fd[i - 1][0], STDIN);
				close(fd[i - 1][0]);
				// }
				if (i + 1 != s->pipe.count_commands)
				{
					// printf("1i: |%d|\n", i);
					// printf("1com: |%d|\n", s->pipe.count_commands);
					close(fd[i][0]);
					dup2(fd[i][1], STDOUT);
					close(fd[i][1]);
				}
				else
				{
					// printf("i: |%d|\n", i);
					// printf("com: |%d|\n", s->pipe.count_commands);
					for (int k = 0; k < s->pipe.count_commands; k++)
					{
						// if (k != i)
							close(fd[k][0]);
						close(fd[k][1]);
					}
				}
			}
			execve(s->var.bin, s->mass3d[i], s->env);
			ft_error(s->mass3d[i][0], 1);
			exit (1);
		}
		// else
		// {
		// 	close(fd[i][1]);
		// }
		if (res)
			ft_memdel_1d(s->var.bin);
	}
	for (int i = 0; i < s->pipe.count_commands; i++)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	if (waitpid(id, &status, 0) > 0)
		return (status);
	return (0);
}








// for(i = 0; i < s->pipe.count_commands; i++) // ls | cat -e | cat -e
// 	{
// 		mini_bin1(s, i);
// 		pipe(fd[i]);
// 		id = fork();
// 		if (id == 0)
// 		{
// 			if (i == 0) // first
// 			{
// 				for (int k = 0; i < s->pipe.count_pipe; k++)
// 				{
// 					if (k != i)
// 						close(fd[k][0]);
// 					close(fd[k][1]);
// 				}
// 				if (i + 1 != s->pipe.count_commands)
// 					dup2(fd[i][1], 1);
// 			}
// 			else
// 			{
// 				dup2(fd[i - 1][0], 0);
// 				close(fd[i - 1][0]);
// 				close(fd[i - 1][1]);
// 			}
// 			// if (i + 1 != s->pipe.count_commands) // if not last
// 			// {
// 			// 	dup2(fd[i][1], 1);
// 			// 	close(fd[i][1]);
// 			// 	close(fd[i][0]);
// 			// }
// 			execve(s->var.bin, s->mass3d[i], s->env);
// 			ft_error(s->mass3d[i][0], 1);
// 			exit (1);
// 		}

// 	}
// 	// for (int i = 0; i < s->pipe.count_pipe; i++)
// 	// {
// 	// 	close(fd[i][0]);
// 	// 	close(fd[i][1]);
// 	// }
// 	if (waitpid(id, &status, 0) > 0)
// 		return (status);


















// tmpin = dup(0);
// 	tmpout = dup(1);
// 	// if (infile)
// 	// 	fdin = open(infile, O_RDONLY);
// 	// else
// 		fdin = dup(0);
// 	int	ret;
// 	int	fdout;
// 	for(i = 0; i < s->pipe.count_commands; i++)
// 	{
// 		res = 0;
// 		res = mini_bin1(s, i);
// 		dup2(fdin, 0);
// 		close(fdin);
// 		if (i == s->pipe.count_commands - 1)
// 		{
// 			// if (outfile)
// 			// 	fdout = open();
// 			// else
// 			fdout = dup(tmpout);
// 		}
// 		else
// 		{
// 			// int fdpipe[2];
// 			pipe(fdpipe);
// 			fdout = fdpipe[1];
// 			fdin = fdpipe[0];
// 		}
// 		dup2(fdout, 1);
// 		close(fdout);
// 		ret = fork();
// 		if (ret == 0)
// 		{
// 			// printf("|%s|\n", s->var.bin);
// 			execve(s->var.bin, s->mass3d[i], s->env);
// 			ft_error(s->mass3d[i][0], 1);
// 			exit (1);
// 		}
// 		if (res)
// 			ft_memdel_1d(s->var.bin);
// 	}
// 	dup2(tmpin, 0);
// 	dup2(tmpout, 1);
// 	close(tmpin);
// 	close(tmpout);
// 	if (waitpid(ret, &status, 0) > 0)
// 		return (status);
// 	return (0);