/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:45:27 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/17 15:05:10 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	}
}