/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:46:08 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/21 19:13:36 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				mini_oldpwd(t_mini *s)
{
	t_mass			*tmp;
	char			*line;
	char			*tmp_1;
	int				flag = 0;

	tmp_1 = NULL;
	line = NULL;
	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
			tmp_1 = ft_strdup(tmp->content + 4);
		tmp = tmp->next;
	}
	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			flag = 1;
			ft_memdel_1d(tmp->content);
			tmp->content = ft_strjoin("OLDPWD=", tmp_1);
			ft_memdel_1d(tmp_1);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = ft_strjoin_free("OLDPWD=", tmp_1, tmp_1);
		my_lstadd_back(&s->head, my_lstnew(line));
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
		s->free_line = put_quotes(line);
		my_lstadd_back(&s->head_x, my_lstnew(s->free_line));
		ft_memdel_1d(s->free_line);
	}
}

void				mini_pwd_1(t_mini *s)
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
			tmp->content = ft_strjoin_free("PWD=", line, line);
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
			line = ft_strjoin_free("PWD=", line, line);
			tmp->content = put_quotes(line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
}

void				mini_pwd(t_mini	*s)
{
	char			*s1;

	s1 = NULL;
	s1 = malloc(1000);
	getcwd(s1, 100);
	write(s->fdout, s1, ft_strlen(s1));
	write(s->fdout, "\n", 1);
	ft_memdel_1d(s1);
}