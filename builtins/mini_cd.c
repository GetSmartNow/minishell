/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:32:58 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/27 17:01:13 by ctycho           ###   ########.fr       */
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
			tmp->content = put_quotes(tmp->content);
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
	while (tmp != NULL)
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
	while (tmp != NULL)
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

static void			empty_olpwd(t_mini *s)
{
	t_mass			*tmp;
	char			*line;

	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			ft_bzero(tmp->content, ft_strlen(tmp->content));
			tmp->content = ft_strdup("OLDPWD=");
		}
		tmp = tmp->next;
	}
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			ft_bzero(tmp->content, ft_strlen(tmp->content));
			tmp->content = put_quotes("OLDPWD=");
		}
		tmp = tmp->next;
	}
}

void				mini_cd(t_mini *s)
{
	int				res;
	t_mass			*tmp;

	if (s->mass3d[0][1] == NULL)
		return ;
	res = 0;
	if (s->var.pwd == 0)
		mini_oldpwd(s);
	else
		empty_olpwd(s);
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
