/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:46:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/22 03:26:41 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			export_to_export_1(t_mini *s, char *arg, int flag, int eq)
{
	t_mass			*tmp;
	int				length;

	tmp = s->head_x;
	while (tmp != NULL && flag == 0)
	{
		if (eq == 1)
		{
			length = length_to_equal(s, arg);
			if (ft_strncmp(tmp->content, arg, length) == 0)
			{
				flag = 1;
				ft_memdel_1d(tmp->content);
				ft_bzero(tmp->content, ft_strlen(tmp->content));
				tmp->content = ft_strdup(arg);
			}
		}
		else
		{
			if (ft_strncmp(tmp->content, arg, ft_strlen(arg)) == 0)
				flag = 1;
		}
		tmp = tmp->next;
	}
	return (flag);
}

void				export_to_export(t_mini *s, int i, int equal)
{
	char			*line;
	int				flag;

	flag = 0;
	line = NULL;
	while (s->mass3d[0][i])
	{
		flag = export_to_export_1(s, s->mass3d[0][i], flag, equal);
		if (flag == 0)
		{
			line = put_quotes(s->mass3d[0][i]);
			my_lstadd_back(&s->head_x, my_lstnew(line));
		}
		i++;
	}
	ft_list_sort(&s->head_x);
}

int					valid_arg(t_mini *s, char *arg)
{
	int				i;
	int				res;

	i = 0;
	res = 0;
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

static void			mini_export_out(t_mini *s)
{
	t_mass			*tmp;

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

void				mini_export(t_mini *s)
{
	int				i;

	i = 1;
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
		mini_export_out(s);
}
