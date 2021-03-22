/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_p2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:23:06 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/22 21:59:14 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				ft_list_to_2d(t_mini *s)
{
	t_mass			*tmp;
	char			*line;
	int				i;

	i = 0;
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
	char			*line;

	line = NULL;
	folder = opendir(dir);
	if (folder == NULL)
	{
		return (-10);
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

int					absolute_path(t_mini *s, char *bin, char *exec)
{
	int				length_dir;
	int				length_com;

	if (ft_strncmp(bin, exec, ft_strlen(bin)) == 0)
		s->var.count_bin++;
	if (s->var.count_bin == 2)
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

void				bin_error_p2(t_mini *s, char *exec, int res)
{
	write(1, "bash: ", 6);
	write(1, exec, ft_strlen(exec));
	if (res == 1 || res == 3)
	{
		write(STDERR, ": No such file or directory\n", 28);
		g_sig.exit_status = 127;
	}
	else if (res == 2)
	{
		write(STDERR, ": is a directory\n", 17);
		g_sig.exit_status = 126;
	}
	else if (res == 5)
	{
		write(STDERR, ": command not found\n", 20);
		g_sig.exit_status = 127;
	}
}

void				bin_error(t_mini *s, char *exec, int res, int status)
{
	if (res == 4 || res == 6 || res == 0 || res == -1)
	{
		if (status == 256)
			g_sig.exit_status = 1;
		else
			g_sig.exit_status = 0;
		return ;
	}
	else
		bin_error_p2(s, exec, res);
}
