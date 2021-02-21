/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:46:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/21 03:22:17 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			length_to_equal(t_mini *s, char *line)
{
	int				i = 0;
	int				count = 0;

	while (line[i] != '=')
	{
		i++;
	}
	return (i);
}

static char			*put_quotes(char *s, char *s1)
{
	int		i = 0;
	int		j = 0;
	while (s1[i])
	{
		s[i] = s1[j];
		if (s1[j] == '=')
		{
			i++;
			s[i] = '"';
		}
		i++;
		j++;
		
	}
}

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
		flag = 0;
		tmp = s->head_x;
		while (tmp != NULL && flag == 0)
		{
			// printf("|%s|\n", tmp->content);
			if (equal == 1)
			{
				length = length_to_equal(s, s->mass3d[0][i]);
				printf("|%d|\n", length);
				if (ft_strncmp(tmp->content, s->mass3d[0][i], length) == 0)
				{
					printf("2|%s|\n", tmp->content);
					// write(1, "#\n", 2);
					// flag = 2;
					deletelem(tmp);
				}
			}
			else
			{
				if (ft_strncmp(tmp->content, s->mass3d[0][i], ft_strlen(s->mass3d[0][i])) == 0)
				{
					write(1, "&\n", 2);
					flag = 1;
				}
			}	
			tmp = tmp->next;
		}
		if (flag == 0)
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
			// write(1, "#\n", 2);
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