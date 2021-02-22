/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:57:51 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/22 17:36:12 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				mini_unset(t_mini *s)
{
	t_mass			*tmp;
	t_mass			*tmp1;
	int				length;
	int				length1;
	int				flag;
	int				count;
	int				i = 1;

	while (s->mass3d[0][i])
	{
		printf("1|%s|\n", s->mass3d[0][i]);
		count = 0;
		tmp = s->head;
		while (tmp != NULL)
		{
			count++;
			length = length_to_equal(s, s->mass3d[0][i]);
			length1 = length_to_equal(s, tmp->content);
			if (ft_strncmp(tmp->content, s->mass3d[0][i], length) == 0 && length1 == length)
			{
				if (count == 1)
					s->head = s->head->next;
				deletelem(tmp);
			}	
			tmp = tmp->next;
		}
		count = 0;
		tmp1 = s->head_x;
		while (tmp1 != NULL)
		{
			count++;
			length = length_to_equal(s, s->mass3d[0][i]);
			length1 = length_to_equal(s, tmp1->content);
			if (ft_strncmp(tmp1->content, s->mass3d[0][i], length) == 0 && length1 == length)
			{	
				if (count == 1)
					s->head_x = s->head_x->next;
				deletelem(tmp1);
				}
			tmp1 = tmp1->next;
		}
		i++;
	}
}