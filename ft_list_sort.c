/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:53:38 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/22 18:01:18 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_list_sort(t_mass **lst, int cmp)
{
	t_mass		*tmp;
	t_mass		*cur;
	t_mass		*nex;

	cur = *(lst);
	while (tmp->next != NULL)
	{
		tmp = cur;
		nex = cur->next;
		if (ft_strcmp(tmp->content[0], nex->content[0]) > 0)
		{
			cur = nex;
			cur->next = tmp;
		}
		else
		{
			cur = cur->next;
		}
	}
}
