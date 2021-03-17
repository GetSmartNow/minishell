/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:46:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/16 14:46:37 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int					valid_arg(t_mini *s, char *arg)
{
	int				i = 0;
	int				res = 0;

	while (arg[i])
	{
		if (arg[0] >= '0' && arg[0] <= '9')
			return (-1);
		if (arg[i] == '+' || arg[i] == '-' || arg[i] == ':' || \
			arg[i] == '.' || arg[i] == ',' || \
			arg[i] == '$' || arg[i] == '*' || arg[i] == '#')
			return (-1);
		i++;
	}
	return (res);
}

void				mini_export(t_mini *s)
{
	t_mass			*tmp;
	int				i = 1;

	if (s->mass3d[0][1])
	{
		while (s->mass3d[0][i])
		{
			if (valid_arg(s, s->mass3d[0][i]) == -1)
			{
				write(STDERR, "bash: export: `", 15);
				write(STDERR, s->mass3d[0][i], ft_strlen(s->mass3d[0][i]));
				write(STDERR, "': not a valid identifier\n", 26);
			}
			else if (ft_strchr(s->mass3d[0][i], '='))
			{
				export_to_env(s, i);
				export_to_export(s, i, 1);
			}
			else
				export_to_export(s, i, 0);
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