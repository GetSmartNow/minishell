/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:41:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/17 00:06:54 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			mini_oldpwd(t_mini *s)
{
	t_mass			*tmp;
	char			*line;

	line = NULL;
	tmp = s->head;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			free(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			tmp->content = ft_strjoin("OLDPWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
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
}

void				mini_cd(t_mini *s)
{
	int				res;
	t_mass			*tmp;
	char			*line = NULL;

	res = 0;
	mini_oldpwd(s);
	res = chdir(s->arg[1]);
	if (res == -1)
	{
		write(1, "cd: ", 4);
		write(1, s->arg[1], ft_strlen(s->arg[1]));
		write(1, ": No such file or directory\n", 28);
	}
	else
		mini_pwd1(s);
}
