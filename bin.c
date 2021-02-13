/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:50:33 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/12 19:24:31 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			mini_env2(t_mini *s)
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
		if (ft_strcmp(command->d_name, s->arg[0]) == 0)
		{
			flag = 1;
			s->var.bin = ft_strjoin(s->var.bin, s->arg[0]);
		}
	}
	closedir(folder);
	return (flag);
}

static char		*mini_env1(t_mini *s)
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
	ft_memdel_arr((void**)bin);
	return (s->tmp);
}

int		mini_bin(t_mini *s)
{
	pid_t			pid;
	int				res = 0;
	int				status;
	char			*bin = NULL;

	s->var.bin = mini_env1(s);
	ft_memdel(s->tmp);
	res = mini_env2(s);
	pid = fork();
	if (pid < 0)
	{
		write(1, "error\n", 6);
		exit (127);
	}
	else if (pid == 0)
	{
		execve(s->var.bin, s->arg, s->env);
		exit (1);
	}
	if (res)
		ft_memdel(s->var.bin);
	if (res == 0)
	{
		write(1, "bash: ", 6);
		write(1, s->arg[0], ft_strlen(s->arg[0]));
		write(1, ": command not found\n", 20);
	}
	if (waitpid(pid, &status, 0) > 0)
		return (status);
	return (0);
}