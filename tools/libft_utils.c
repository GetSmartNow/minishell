/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:43:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/21 00:32:42 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mass	*my_lstnew(void *content)
{
	t_mass	*new;

	new = malloc(sizeof(t_mass));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void			my_lstadd_back(t_mass **lst, t_mass *new)
{
	t_mass	*end;
	t_mass	*tmp;

	if (lst == NULL)
		return ;
	end = *lst;
	if (end == NULL)
		*lst = new;
	else
	{
		while (end->next != NULL)
			end = end->next;
		new->prev = end;
		end->next = new;
	}
}

// void			my_lstadd_back(t_mass **lst, t_mass *new)
// {
// 	t_mass	*end;

// 	if (lst == NULL)
// 		return ;
// 	end = *lst;
// 	if (end == NULL)
// 		*lst = new;
// 	else
// 	{
// 		while (end->next != NULL)
// 			end = end->next;
// 		end->next = new;
// 	}
// }

void	my_lstdelone(t_mass *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}