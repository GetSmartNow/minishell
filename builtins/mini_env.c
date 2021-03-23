/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:45:27 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/23 21:49:03 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			export_to_env_1(t_mini *s, char *arg, int flag)
{
	t_mass			*tmp;
	int				length;

	tmp = s->head;
	while (tmp != NULL)
	{
		length = length_to_equal(arg);
		if (ft_strncmp(tmp->content, arg, length) == 0)
		{
			flag = 1;
			ft_memdel_1d(tmp->content);
			ft_bzero(tmp->content, ft_strlen(tmp->content));
			tmp->content = ft_strdup(arg);
		}
		tmp = tmp->next;
	}
	return (flag);
}

void				export_to_env(t_mini *s, int i)
{
	char			*line;
	int				flag;

	flag = 0;
	line = NULL;
	while (s->mass3d[0][i])
	{
		flag = export_to_env_1(s, s->mass3d[0][i], flag);
		if (flag == 0)
		{
			line = ft_strdup(s->mass3d[0][i]);
			my_lstadd_back(&s->head, my_lstnew(line));
		}
		i++;
	}
	ft_list_sort(&s->head);
}

void				mini_env(t_mini *s)
{
	t_mass			*tmp;
	int				i;

	i = 0;
	if (s->mass3d[0][1])
	{
		write(1, "env: ", 5);
		write(1, s->mass3d[0][1], ft_strlen(s->mass3d[0][1]));
		write(1, ": No such file or directory\n", 28);
		g_sig.exit_status = 127;
	}
	else
	{
		ft_list_sort(&s->head);
		tmp = s->head;
		while (tmp != NULL)
		{
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
			tmp = tmp->next;
			i++;
		}
		g_sig.exit_status = 0;
	}
}
