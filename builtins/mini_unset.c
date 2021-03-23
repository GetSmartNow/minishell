/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:57:51 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/23 21:48:13 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				mini_unset_export(t_mini *s, t_mass *tmp, char *arg)
{
	int				count;
	int				length;
	int				length1;

	count = 0;
	tmp = s->head_x;
	while (tmp != NULL)
	{
		count++;
		length = length_to_equal(arg);
		length1 = length_to_equal(tmp->content);
		if (ft_strncmp(tmp->content, arg, length) == 0 && length1 == length)
		{
			if (count == 1)
				s->head_x = s->head_x->next;
			deletelem(tmp);
		}
		tmp = tmp->next;
	}
}

void				mini_unset_env(t_mini *s, t_mass *tmp, char *arg)
{
	int				count;
	int				length;
	int				length1;

	count = 0;
	tmp = s->head;
	while (tmp != NULL)
	{
		count++;
		length = length_to_equal(arg);
		length1 = length_to_equal(tmp->content);
		if (ft_strncmp(tmp->content, arg, length) == 0 && length1 == length)
		{
			if (ft_strncmp(tmp->content, "PATH=", ft_strlen("PATH=")) == 0)
				s->var.path = ft_strdup(tmp->content + 5);
			if (count == 1)
				s->head = s->head->next;
			deletelem(tmp);
		}
		tmp = tmp->next;
	}
}

void				mini_unset(t_mini *s)
{
	t_mass			*tmp;
	int				i;

	i = 1;
	tmp = NULL;
	while (s->mass3d[0][i])
	{
		if (ft_strncmp("PWD", s->mass3d[0][i], ft_strlen("PWD")) == 0)
			s->var.pwd = 1;
		mini_unset_env(s, tmp, s->mass3d[0][i]);
		mini_unset_export(s, tmp, s->mass3d[0][i]);
		i++;
	}
}
