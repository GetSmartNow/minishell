/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:32:58 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/06 23:19:34 by ctycho           ###   ########.fr       */
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
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
			line = ft_strdup(tmp->content + 4);
		tmp = tmp->next;
	}
	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			flag = 1;
			free(tmp->content);
			tmp->content = ft_strjoin("OLDPWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = ft_strjoin("OLDPWD=", line);
		my_lstadd_back(&s->head, my_lstnew(line));
		// ft_memdel_1d(line);
	}


	flag = 0;
	line = NULL;
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
			line = ft_strdup(tmp->content + 4);
		tmp = tmp->next;
	}
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD", ft_strlen("OLDPWD")) == 0)
		{
			flag = 1;
			free(tmp->content);
			tmp->content = ft_strjoin("OLDPWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = ft_strjoin("OLDPWD=", line);
		line = put_quotes(line);
		my_lstadd_back(&s->head_x, my_lstnew(line));
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

static void			mini_cd_minus_1(t_mini *s)
{
	t_mass			*tmp;
	char			*line;
	int				flag = 0;

	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			flag = 1;
			if (ft_strlen(tmp->content) == ft_strlen("OLDPWD="))
				write(1, "bash: cd: OLDPWD not set\n", 25);
			else
				s->var.oldpwd = ft_strdup(tmp->content + 7);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		write(1, "bash: cd: OLDPWD not set\n", 25);
}

static int			mini_cd_minus(t_mini *s, char *exec, char *arg)
{
	int				res;
	int				i;

	i = 0;
	while (arg[i] == '-')
		i++;
	printf("i: %d\n", i);
	if (i != 1 && arg[1] != '-')
	{
		write(1, "bash: cd: ", 10);
		write(1, &arg[0], 1);
		write(1, &arg[1], 1);
		write(1, ": invalid option\n", 17);
		write(1, "cd: usage: cd [-L|-P] [dir]\n", 28);
	}
	else if (arg[0] == '-')
		mini_cd_minus_1(s);
	if (s->var.oldpwd != NULL)
		res = chdir(s->var.oldpwd);
	else
		res = chdir(arg);
	return (res);
}

void				mini_cd(t_mini *s, char *exec, char *arg)
{
	int				res;
	int				flag;
	t_mass			*tmp;

	res = 0;
	if (arg == NULL)
		return ;
	res = mini_cd_minus(s, exec, arg);
	if (res == -1 && s->mass3d[0][1][0] != '-')
	{
		write(1, "bash: cd: ", 10);
		write(1, arg, ft_strlen(arg));
		write(1, ": No such file or directory\n", 28);
	}
	else
	{
		if (s->var.pwd == 0)
			mini_oldpwd(s);
		else
			empty_olpwd(s);
		mini_pwd_1(s);
	}
}
