/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:05:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/17 21:13:10 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			mini_bin2(t_mini *s)
{
	DIR				*folder;
	struct dirent	*command;
	int				flag;

	flag = 0;
	folder = opendir(s->var.bin);
	if (folder == NULL)
	{
		write(1, "error\n", 6);
		exit (127);
	}
	while ((command = readdir(folder)))
	{
		if (ft_strcmp(command->d_name, s->mass3d[1][0]) == 0) //if (ft_strcmp(command->d_name, s->arg[0]) == 0)
		{
			flag = 1;
			s->var.bin = ft_strjoin(s->var.bin, s->div_pipe[1]); //s->var.bin = ft_strjoin(s->var.bin, s->arg[0]);
		}
	}
	closedir(folder);
	return (flag);
}

static char		*mini_bin1(t_mini *s)
{
	char		**bin = NULL;
	int			i = 0;

	s->tmp = NULL;
	while (ft_strncmp(s->env[i], "PATH=", 5) != 0)
		i++;
	bin = ft_split(s->env[i], ':');
	s->tmp = bin[0];
	s->tmp = ft_strnstr(s->tmp, "/bin", ft_strlen(s->tmp));
	s->tmp = ft_strjoin(s->tmp, "/");
	ft_memdel_2d((void**)bin);
	return (s->tmp);
}

int					mini_pipes(t_mini *s)
{
	int		tmpin = 0;
	int		tmpout = 0;
	int		fdin = 0;
	int		i;
	int				status;
	int		res = 0;

	tmpin = dup(0);
	tmpout = dup(1);
	// if (infile)
	// 	fdin = open(infile, O_RDONLY);
	// else
		fdin = dup(0);
	int	ret;
	int	fdout;
	s->var.bin = mini_bin1(s);
	res = mini_bin2(s);
	printf("|%s|\n", s->var.bin);
	for(i = 0; i < s->pipe.count_commands; i++)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == s->pipe.count_commands - 1)
		{
			// if (outfile)
			// 	fdout = open();
			// else
			fdout = dup(tmpout);
		}
		else
		{
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// dup2(fdout, 1);
		// close(fdout);
		
		ret = fork();
		if (ret == 0)
		{
			execve(s->var.bin, s->mass3d[i], s->env);
			// perror("error");
			exit (1);
		}
		// if (res)
		// 	ft_memdel_1d(s->var.bin);
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	if (waitpid(ret, &status, 0) > 0)
		return (status);
	return (0);
}
