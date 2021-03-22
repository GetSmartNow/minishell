/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipes_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:37:10 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/23 00:10:42 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					magic_box_p2(t_mini *s, char *dir, char *exec, int f)
{
	DIR				*folder;
	struct dirent	*command;
	char			*line;

	folder = opendir(dir);
	if (folder == NULL)
	{
		write(1, "error\n", 6);
		exit(127);
	}
	while ((command = readdir(folder)))
	{
		if (ft_strcmp(command->d_name, exec) == 0)
		{
			f = 1;
			line = ft_strjoin(dir, "/");
			s->var.bin = ft_strjoin(line, exec);
			ft_memdel_1d(line);
		}
	}
	closedir(folder);
	return (f);
}

int					mini_bin_p1(t_mini *s, char *exec, int i)
{
	char			**bin;
	char			*line;
	t_mass			*tmp;
	int				m;
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
		m = -1;
		while (bin[++m] && flag == 0)
			flag = magic_box_p2(s, bin[m], exec, flag);
	}
	ft_memdel_2d((void**)bin);
	return (flag);
}
