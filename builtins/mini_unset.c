/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:57:51 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/21 23:18:16 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				mini_unset(t_mini *s)
{
	t_mass			*tmp;
	t_mass			*tmp1;
	int				length;
	int				flag;
	int				i = 1;

	while (s->mass3d[0][i])
	{
		flag = 0;
		printf("1|%s|\n", s->mass3d[0][i]);
		tmp = s->head;
		while (tmp != NULL && flag == 0)
		{
			length = length_to_equal(s, s->mass3d[0][i]);
			if (ft_strncmp(tmp->content, s->mass3d[0][i], length) == 0)
			{
				deletelem(tmp);
			}	
			tmp = tmp->next;
		}
		tmp1 = s->head_x;
		while (tmp1 != NULL && flag == 0)
		{
			length = length_to_equal(s, s->mass3d[0][i]);
			if (ft_strncmp(tmp1->content, s->mass3d[0][i], length) == 0)
			{
				deletelem(tmp1);
			}	
			tmp1 = tmp1->next;
		}
		i++;
	}
}