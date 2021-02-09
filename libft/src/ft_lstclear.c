/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:15:10 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/08 19:50:47 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*el;

	if (!del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		el = *lst;
		*lst = el->next;
		free(el);
	}
	*lst = NULL;
}
