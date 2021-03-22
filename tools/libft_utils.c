/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:43:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/22 15:11:36 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mass			*my_lstnew(void *content)
{
	t_mass		*new;

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
	t_mass		*end;

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

t_mass			*deletelem(t_mass *lst)
{
	t_mass		*prev;
	t_mass		*next;

	prev = lst->prev;
	next = lst->next;
	if (prev != NULL)
		prev->next = lst->next;
	if (next != NULL)
		next->prev = lst->prev;
	free(lst->content);
	free(lst);
	return (prev);
}

void			ft_list_sort(t_mass **lst)
{
	t_mass		*ptr;
	t_mass		*ptr1;
	t_mass		*next;
	char		*tmp;

	ptr = *(lst);
	while (ptr != NULL)
	{
		ptr1 = *(lst);
		while (ptr1->next != NULL)
		{
			if (ft_strcmp(ptr1->content, ptr1->next->content) > 0)
			{
				tmp = ptr1->content;
				ptr1->content = ptr1->next->content;
				ptr1->next->content = tmp;
			}
			ptr1 = ptr1->next;
		}
		ptr = ptr->next;
	}
}
