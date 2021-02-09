/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:12:35 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/08 19:47:47 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *iter;

	if (lst != NULL)
	{
		iter = lst;
		while (1)
		{
			(*f)(iter->content);
			iter = iter->next;
			if (iter == NULL)
				return ;
		}
	}
}
