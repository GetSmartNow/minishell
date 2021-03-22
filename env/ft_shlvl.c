/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:33:50 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/22 06:05:03 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void			ft_shlvl_export_p2(t_mini *s, char *content, char *tmp_sh)
{
	char			*line;

	s->var.shlvl = mini_atoi(content);
	s->var.shlvl++;
	if (s->var.shlvl == 1000)
	{
		ft_memdel_1d(content);
		content = put_quotes("SHLVL=""");
	}
	else
	{
		tmp_sh = ft_itoa(s->var.shlvl);
		ft_memdel_1d(content);
		line = ft_strjoin_free("SHLVL=", tmp_sh, tmp_sh);
		content = put_quotes(line);
		ft_memdel_1d(line);
	}
}

static int			ft_shlvl_export(t_mini *s, char *tmp_sh, int f)
{
	t_mass			*tmp;
	char			*line;

	f = 0;
	tmp_sh = NULL;
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "SHLVL=", 6) == 0)
		{
			f = check_shlvl(s, tmp->content, 1);
			if (f == 1)
				ft_shlvl_export_p2(s, tmp->content, tmp_sh);
			else if (f == 2)
			{
				ft_memdel_1d(tmp->content);
				tmp->content = put_quotes("SHLVL=1");
			}
		}
		tmp = tmp->next;
	}
	return (f);
}

static int			ft_shlvl_env(t_mini *s, char *content, char *tmp_sh, int f)
{
	f = check_shlvl(s, content, 0);
	if (f == 1)
	{
		s->var.shlvl = mini_atoi(content);
		s->var.shlvl++;
		if (s->var.shlvl == 1000)
		{
			ft_memdel_1d(content);
			content = ft_strdup("SHLVL=");
		}
		else
		{
			tmp_sh = ft_itoa(s->var.shlvl);
			ft_memdel_1d(content);
			content = ft_strjoin_free("SHLVL=", tmp_sh, tmp_sh);
		}
	}
	else if (f == 2)
	{
		ft_memdel_1d(content);
		content = ft_strdup("SHLVL=1");
	}
	return (f);
}

void				ft_shlvl(t_mini *s)
{
	t_mass			*tmp;
	int				flag;
	char			*line;
	char			*tmp_sh;

	flag = 0;
	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "SHLVL=", 6) == 0)
			flag = ft_shlvl_env(s, tmp->content, tmp_sh, flag);
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = ft_strdup("SHLVL=1");
		my_lstadd_back(&s->head, my_lstnew(line));
	}
	flag = ft_shlvl_export(s, tmp_sh, flag);
	if (flag == 0)
	{
		line = put_quotes("SHLVL=1");
		my_lstadd_back(&s->head_x, my_lstnew(line));
	}
}
