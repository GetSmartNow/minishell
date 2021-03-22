/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:53:47 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/22 05:27:24 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		get_pwd_export(t_mini *s, t_mass *tmp, int flag)
{
	char		*line;
	char		*free_str;

	line = NULL;
	free_str = NULL;
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
		{
			flag = 1;
			ft_memdel_1d(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			free_str = ft_strjoin_free("PWD=", line, line);
			tmp->content = put_quotes(free_str);
			ft_memdel_1d(free_str);
		}
		tmp = tmp->next;
	}
	return (flag);
}

void			get_pwd_env(t_mini *s, t_mass *tmp, int flag)
{
	char		*line;

	line = NULL;
	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
		{
			flag = 1;
			ft_memdel_1d(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			tmp->content = ft_strjoin("PWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		s->free_line = malloc(1000);
		getcwd(s->free_line, 100);
		line = ft_strjoin_free("PWD=", s->free_line, s->free_line);
		my_lstadd_back(&s->head, my_lstnew(line));
	}
}

void			get_pwd(t_mini *s)
{
	t_mass		*tmp;
	char		*line;
	char		*free_str;
	int			flag;

	flag = 0;
	line = NULL;
	free_str = NULL;
	get_pwd_env(s, tmp, flag);
	flag = get_pwd_export(s, tmp, flag);
	if (flag == 0)
	{
		line = malloc(1000);
		getcwd(line, 100);
		s->free_line = ft_strjoin("PWD=", line);
		ft_memdel_1d(line);
		free_str = put_quotes(s->free_line);
		ft_memdel_1d(s->free_line);
		my_lstadd_back(&s->head_x, my_lstnew(free_str));
	}
}
