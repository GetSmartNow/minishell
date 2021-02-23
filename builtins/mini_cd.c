/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:41:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/23 13:46:09 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			mini_oldpwd(t_mini *s)
{
	t_mass			*tmp;
	char			*line;
	int				flag = 0;

	line = NULL;
	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			flag = 1;
			free(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			tmp->content = ft_strjoin("OLDPWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = malloc(1000);
		getcwd(line, 100);
		line = ft_strjoin("OLDPWD=", line);
		my_lstadd_back(&s->head, my_lstnew(line));
	}
	flag = 0;
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD", ft_strlen("OLDPWD")) == 0)
		{
			flag = 1;
			free(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			tmp->content = ft_strjoin("OLDPWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = malloc(1000);
		getcwd(line, 100);
		line = ft_strjoin("OLDPWD=", line);
		my_lstadd_back(&s->head_x, my_lstnew(line));
	}
}

static void			mini_pwd1(t_mini *s)
{
	t_mass			*tmp;
	char			*line;

	tmp = s->head;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
		{
			free(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			tmp->content = ft_strjoin("PWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
	tmp = s->head_x;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
		{
			free(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			tmp->content = ft_strjoin("PWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
}

void				mini_cd(t_mini *s)
{
	int				res;
	t_mass			*tmp;

	if (s->mass3d[0][1] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	res = 0;
	mini_oldpwd(s);
	res = chdir(s->mass3d[0][1]);
	if (res == -1)
	{
		write(1, "cd: ", 4);
		write(1, s->mass3d[0][1], ft_strlen(s->mass3d[0][1]));
		write(1, ": No such file or directory\n", 28);
	}
	else
		mini_pwd1(s);
}
