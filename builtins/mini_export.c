/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:46:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/21 23:00:08 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*put_quotes(char *s, char *s1)
{
	int		i = 0;
	int		j = 0;
	int		flag = 0;

	s = (char *)malloc(sizeof(char) * ft_strlen(s1) + 3);
	while (s1[j])
	{
		s[i] = s1[j];
		if (s1[j] == '=')
		{
			s[++i] = '"';
			flag = 1;
		}
		if (s1[j + 1] == '\0' && flag == 1)
			s[++i] = '"';
		i++;
		j++;
	}
	s[i] = '\0';
	return(s);
}

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
					deletelem(tmp);
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
			line = put_quotes(line, s->mass3d[0][i]);
			my_lstadd_back(&s->head_x, my_lstnew(line));
		}
		i++;
	}
}

void				export_to_env(t_mini *s, int i)
{
	t_mass			*tmp;
	char			*line = NULL;
	int				flag;
	int				length;

	while (s->mass3d[0][i])
	{
		// printf("|%s|\n", s->mass3d[0][i]);
		flag = 0;
		tmp = s->head;
		while (tmp != NULL)
		{
			length = length_to_equal(s, s->mass3d[0][i]);
			if (ft_strncmp(tmp->content, s->mass3d[0][i], length) == 0)
			{
				deletelem(tmp);
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
}

void				mini_export(t_mini *s)
{
	t_mass			*tmp;
	int				i = 1;

	tmp = s->head_x;
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
		while (tmp != NULL)
		{
			write(1, "declare -x ", 11);
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
			tmp = tmp->next;
		}
	}
}