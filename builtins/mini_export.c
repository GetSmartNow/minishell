/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:46:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/21 00:40:17 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				export_to_export(t_mini *s, int equal)
{
	t_mass			*tmp;
	t_mass			*tmp1;
	char			*line = NULL;
	int				i = 1;
	int				flag;
	int				length;

	while (s->mass3d[0][i])
	{
		printf("1|%s|\n", s->mass3d[0][i]);
		flag = 1;
		tmp = s->head_x;
		while (tmp != NULL && flag == 1)
		{
			// printf("|%s|\n", tmp->content);
			if (equal == 1)
			{
				length = ft_strlen(s->mass3d[0][i]);
				length = length - 1;
				if (ft_strncmp(tmp->content, s->mass3d[0][i], length) == 0)
				{
					printf("2|%s|\n", tmp->content);
					printf("|%d|\n", length);
					write(1, "#\n", 2);
					flag = 0;
					tmp1 = tmp;
					tmp1 = tmp->prev;
					free(tmp1->content);
					line = ft_strdup(s->mass3d[0][i]);
					my_lstadd_back(&s->head_x, my_lstnew(line));
				}
			}
			else
			{
				if (ft_strncmp(tmp->content, s->mass3d[0][i], ft_strlen(s->mass3d[0][i])) == 0)
				{
					write(1, "&\n", 2);
					flag = 0;
				}
			}	
			tmp = tmp->next;
		}
		if (flag == 1)
		{
			write(1, "*\n", 2);
			// if (equal == 1)
			// 	free(tmp->content);
			line = ft_strdup(s->mass3d[0][i]);
			my_lstadd_back(&s->head_x, my_lstnew(line));
		}
		i++;
	}
}

void				export_to_env(t_mini *s)
{
	t_mass			*tmp;
}

void				mini_export(t_mini *s)
{
	t_mass			*tmp;

	tmp = s->head_x;
	if (s->mass3d[0][1])
	{
		// if (ft_strcmp(s->mass3d[0][1], "=") == 0)
		if (ft_strchr(s->mass3d[0][1], '='))
		{
			write(1, "#\n", 2);
			export_to_env(s);
			export_to_export(s, 1);
		}
		else
			export_to_export(s, 0);
	}
	else
	{
		while (tmp != NULL)
		{
			write(1, "declare -x ", 11);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
			tmp = tmp->next;
		}
	}
}