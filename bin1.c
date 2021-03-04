/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:36:22 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/04 18:51:58 by ctycho           ###   ########.fr       */
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

int					magic_box(t_mini *s, char *dir, char *exec)
{
	DIR				*folder;
	struct dirent	*command;
	char			*line = NULL;

	folder = opendir(dir);
	if (folder == NULL)
	{
		write(1, "error\n", 6);
		exit (127);
	}
	while ((command = readdir(folder)))
	{
		if (ft_strcmp(command->d_name, exec) == 0)
		{
			s->var.count_bin++;
			line = ft_strjoin(dir, "/");
			s->var.bin = ft_strjoin(line, exec);
			ft_memdel_1d(line);
		}
	}
	closedir(folder);
	return (0);
}

int				absolute_path(t_mini *s, char *bin, char *exec)
{
	int			length_dir;
	int			length_com;

	if (ft_strncmp(bin, exec, ft_strlen(bin)) == 0)
		s->var.count_bin++; // we have a right directory
	if (s->var.count_bin == 1)
	{
		length_com = ft_strlen(exec);
		length_dir = ft_strlen(bin);
		length_dir++;
		if (length_com > length_dir)
		{
			s->var.count_bin++;
			magic_box(s, bin, exec + length_dir);
		}
	}
	return (s->var.count_bin);
}

char				**exec_bin_2(t_mini *s, char **bin, char *exec)
{
	t_mass		*tmp;

	tmp = s->head;
	while (tmp != NULL && ft_strncmp(tmp->content, "PATH=", 5) != 0)
		tmp = tmp->next;
	if (ft_strncmp(exec, "minishell", 9) == 0 || \
		ft_strncmp(exec, "./minishell", 11) == 0)
	{
		s->var.bin = s->av;
		ft_list_to_2d(s);
	}
	else if (tmp == NULL)
	{
		 s->var.count_bin = -1;
	}
	else if (exec[0] == '/')
		s->var.count_bin = 0;
	else
		s->var.count_bin = 4;
	bin = ft_split(tmp->content + 5, ':');
	return (bin);
}

int					exec_bin_1(t_mini *s, char *exec)
{
	int			i = 0;
	char		**bin;
	char		*path;
	
	bin = exec_bin_2(s, bin, exec);
	if (s->var.count_bin == -1)
		return (-1);
	printf("|%d|\n", s->var.count_bin);
	while (bin[i])
	{
		if (s->var.count_bin == 0)
			absolute_path(s, bin[i], exec);
		else
			magic_box(s, bin[i], exec);
		i++;
	}
	printf("exec |%s|\n", s->var.bin);
	return (s->var.count_bin);
}

int					exec_bin(t_mini *s, char **arr, char *exec)
{
	pid_t			pid;
	int				res = 0;
	char			*bin = NULL;

	exec_bin_1(s, exec);
	pid = fork();
	if (pid < 0)
	{
		write(1, "error\n", 6);
		exit (127);
	}
	else if (pid == 0)
	{
		execve(s->var.bin, arr, s->env);
		exit (1);
	}
	else
		wait(NULL);
	if (res)
		ft_memdel_1d(s->var.bin);
	return (0);
}