/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:46:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/19 19:16:23 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				export_to_export(t_mini *s)
{
	t_mass			*tmp;
	int				i = 0;
	int				flag;

	while (s->mass3d[0][i])
	{
		flag = 1;
		tmp = s->head;
		while (tmp != NULL && flag == 1)
		{
			if (ft_strncmp(tmp->content, s->mass3d[0][i], ft_strlen(s->mass3d[0][i])) == 0)
				flag = 0;
			tmp = tmp->next;
		}
		if (flag == 0)
		{

		}
		i++;
	}
}

void				mini_export(t_mini *s)
{
	t_mass			*tmp;

	tmp = s->head;
	if (s->mass3d[0][1])
	{
		if (ft_strcmp(s->mass3d[0][0], "=") == 0)
			export_to_env(s);
		else
			export_to_export(s);
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