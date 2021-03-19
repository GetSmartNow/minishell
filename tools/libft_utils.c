/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:43:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/08 19:20:46 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	free(lst->content);
	free(lst); // освобождаем память удаляемого элемента
	return(prev);
}

void			ft_list_sort(t_mass **lst)
{
	t_mass		*ptr;
	t_mass		*ptr1;
	t_mass		*next;
	char		*tmp;
	int			i;

	ptr = *(lst);
	while (ptr != NULL)
	{
		ptr1 = *(lst);
		while (ptr1->next != NULL)
		{
			if (ft_strcmp(ptr1->content, ptr1->next->content) > 0)
			{
				// printf("|%s|\n", ptr1->content);
				tmp = ptr1->content;
				// write(1, "#", 1);
				ptr1->content = ptr1->next->content;
				ptr1->next->content = tmp;
			}
			ptr1 = ptr1->next;
		}
		ptr = ptr->next;
	}
}
