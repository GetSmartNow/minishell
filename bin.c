/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:50:33 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/04 11:59:01 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int			magic_box()
// {
// 	DIR				*folder;
// 	struct dirent	*command;

	
// }

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

static int		absolute_path(char *line)
{
	int			i = 1;

	while (line[i] != '\0')
		i++;
	i--;
	while (line[i] != '/')
		i--;
	return (i);
}

// static int		absolute_path(char *line)
// {
	
// }

static int		mini_bin1(t_mini *s, int i)
{
	char		**bin = NULL;
	char		*line = NULL;
	t_mass		*tmp;
	int			m = 0;
	DIR				*folder;
	struct dirent	*command;
	int				flag;
	int				length;
	char			*com = NULL;

	flag = 0;
	tmp = s->head;
	while (tmp != NULL && ft_strncmp(tmp->content, "PATH=", 5) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
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
		if (s->mass3d[i][0][0] == '/')
		{

			m = 0;
			length = absolute_path(s->mass3d[i][0]);
			// printf("bin |%s|\n", bin[m]);
			// printf("arg |%s|\n", s->mass3d[i][0]);
			while (bin[m])
			{
				if (ft_strncmp(bin[m], s->mass3d[i][0], length))
				{
					
				}
			}
			s->var.bin = ft_strdup(s->mass3d[i][0]);
		}
		else
		{
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

	// res = mini_bin1(s, 0);
	// printf("|%s|\n", s->var.bin);
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
	if (res == -1)
	{
		write(1, "bash: ", 6);
		write(1, s->mass3d[0][0], ft_strlen(s->mass3d[0][0]));
		write(1, ": No such file or directory\n", 28);
	}
	else if (res == 0)
	{
		write(1, "bash: ", 6);
		write(1, s->mass3d[0][0], ft_strlen(s->mass3d[0][0]));
		write(1, ": command not found\n", 20);
	}
	if (waitpid(pid, &status, 0) > 0)
		return (status);
	return (0);
}