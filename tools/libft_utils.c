/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:43:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/21 02:51:55 by ctycho           ###   ########.fr       */
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

t_mass			*deletelem(t_mass *lst)
{
	t_mass		*prev;
	t_mass		*next;
	
	prev = lst->prev; // узел, предшествующий lst
	next = lst->next; // узел, следующий за lst
	if (prev != NULL)
		prev->next = lst->next; // переставляем указатель
	if (next != NULL)
		next->prev = lst->prev; // переставляем указатель
	free(lst); // освобождаем память удаляемого элемента
	return(prev);
}

void	my_lstdelone(t_mass *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}