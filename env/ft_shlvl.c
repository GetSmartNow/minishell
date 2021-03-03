/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:33:50 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/02 16:40:13 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			mini_atoi(char *line)
{
	int				i;
	int				res;

	i = 0;
	res = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			res = (res * 10) + (line[i] - 48);
			i++;
		}
		else
			i++;
	}
	return (res);
}

static int				check_shlvl(t_mini *s, char *line, int	sep)
{
	int					i = 0;
	int					flag = 0;

	if (sep == 0)
	{
		while (line[i] != '=')
			i++;
		i++;
		while (line[i] != '\0')
		{
			if (line[i] >= '0' && line[i] <= '9')
				flag = 1;
			else
				return (2);
			i++;
		}
	}
	else if (sep == 1)
	{
		while (line[i] != '=')
			i++;
		i = i + 2;
		while (line[i + 1] != '\0')
		{
			if (line[i] >= '0' && line[i] <= '9')
				flag = 1;
			else
				return (2);
			i++;
		}
	}
	return (flag);
}

void				ft_shlvl(t_mini *s)
{
	t_mass			*tmp;
	int				flag = 0;
	char			*line;

	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "SHLVL=", 6) == 0)
		{
			flag = check_shlvl(s, tmp->content, 0);
			if (flag == 1)
			{
				s->var.shlvl = mini_atoi(tmp->content);
				s->var.shlvl++;
				ft_bzero(tmp->content, ft_strlen(tmp->content));
				tmp->content = ft_strjoin("SHLVL=", ft_itoa(s->var.shlvl));
			}
			else if (flag == 2)
			{
				ft_bzero(tmp->content, ft_strlen(tmp->content));
				tmp->content = ft_strdup("SHLVL=1");
			}
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = ft_strdup("SHLVL=1");
		my_lstadd_back(&s->head, my_lstnew(line));
	}
	flag = 0;
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "SHLVL=", 6) == 0)
		{
			flag = check_shlvl(s, tmp->content, 1);
			if (flag == 1)
			{
				s->var.shlvl = mini_atoi(tmp->content);
				s->var.shlvl++;
				ft_bzero(tmp->content, ft_strlen(tmp->content));
				line = ft_strjoin("SHLVL=", ft_itoa(s->var.shlvl));
				tmp->content = put_quotes(line);
				ft_memdel_1d(line);
			}
			else if (flag == 2)
			{
				ft_bzero(tmp->content, ft_strlen(tmp->content));
				tmp->content = put_quotes("SHLVL=1");
			}
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = put_quotes("SHLVL=1");
		my_lstadd_back(&s->head_x, my_lstnew(line));
	}
}
