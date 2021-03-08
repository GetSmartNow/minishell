/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:46:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/08 19:20:22 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				export_to_export(t_mini *s, int i, int equal)
{
	t_mass			*tmp;
	char			*line = NULL;
	int				flag;
	int				length;

	while (s->mass3d[0][i])
	{
		flag = 0;
		tmp = s->head_x;
		while (tmp != NULL && flag == 0)
		{
			if (equal == 1)
			{
				length = length_to_equal(s, s->mass3d[0][i]);
				if (ft_strncmp(tmp->content, s->mass3d[0][i], length) == 0)
				{
					flag = 1;
					ft_bzero(tmp->content, ft_strlen(tmp->content));
					tmp->content = ft_strdup(s->mass3d[0][i]);
				}
			}
			else
			{
				if (ft_strncmp(tmp->content, s->mass3d[0][i], ft_strlen(s->mass3d[0][i])) == 0)
				{
					flag = 1;
				}
			}	
			tmp = tmp->next;
		}
		if (flag == 0)
		{
			line = put_quotes(s->mass3d[0][i]);
			my_lstadd_back(&s->head_x, my_lstnew(line));
		}
		i++;
	}
	ft_list_sort(&s->head_x);
}

void				export_to_env(t_mini *s, int i)
{
	t_mass			*tmp;
	char			*line = NULL;
	int				flag;
	int				length;

	while (s->mass3d[0][i])
	{
		flag = 0;
		tmp = s->head;
		while (tmp != NULL)
		{
			length = length_to_equal(s, s->mass3d[0][i]);
			if (ft_strncmp(tmp->content, s->mass3d[0][i], length) == 0)
			{
				flag = 1;
				ft_bzero(tmp->content, ft_strlen(tmp->content));
				tmp->content = ft_strdup(s->mass3d[0][i]);
			}	
			tmp = tmp->next;
		}
		if (flag == 0)
		{
			line = ft_strdup(s->mass3d[0][i]);
			my_lstadd_back(&s->head, my_lstnew(line));
		}
		i++;
	}
	ft_list_sort(&s->head);
}

void				mini_export(t_mini *s)
{
	t_mass			*tmp;
	int				i = 1;

	// tmp = s->head_x;
	if (s->mass3d[0][1])
	{
		while (s->mass3d[0][i])
		{
			// printf("1|%s|\n", s->mass3d[0][i]);
			if (ft_strchr(s->mass3d[0][i], '='))
			{
				// write(1, "*\n", 2);
				export_to_env(s, i);
				export_to_export(s, i, 1);
			}
			else
			{
				// write(1, "#\n", 2);
				export_to_export(s, i, 0);
			}
			i++;
		}
	}
	else
	{
		ft_list_sort(&s->head_x);
		tmp = s->head_x;
		while (tmp != NULL)
		{
			write(1, "declare -x ", 11);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
			tmp = tmp->next;
		}
	}
}