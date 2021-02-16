/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:45:27 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/16 12:45:42 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				mini_env(t_mini *s)
{
	t_mass			*tmp;
	int				i;

	i = 0;
	if (s->arg[1])
	{
		write(1, "env: ", 5);
		write(1, s->arg[1], ft_strlen(s->arg[1]));
		write(1, ": No such file or directory\n", 28);
	}
	else
	{
		tmp = s->head;
		while (s->env[i] != NULL)
		{
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
			tmp = tmp->next;
			i++;
		}
	}
}