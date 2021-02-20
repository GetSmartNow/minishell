/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 23:36:05 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/21 00:02:47 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

t_list				*init(t_list *lst, char *a)  // а- значение первого узла
{
	// t_list		*lst;
	
	// lst = (t_list*)malloc(sizeof(t_list));
	lst->content = a;
	lst->next = NULL; // указатель на следующий узел
	lst->prev = NULL; 
	return(lst);
}

t_list				*addelem(t_list *lst, char *number)
{
	t_list *temp, *p;
	temp = (t_list*)malloc(sizeof(t_list));
	p = lst->next; // сохранение указателя на следующий узел
	lst->next = temp; // предыдущий узел указывает на создаваемый
	temp->content = number; // сохранение поля данных добавляемого узла
	temp->next = p; // созданный узел указывает на следующий узел
	temp->prev = lst; // созданный узел указывает на предыдущий узел
	if (p != NULL)
		p->prev = temp;
	return(temp);
}

void listprint(t_list *lst)
{
	t_list *p;
	p = lst;
	while (p != NULL) // условие окончания обхода
	{
		printf("%s\n", p->content); // вывод значения элемента p
		p = p->next; // переход к следующему узлу
	}
}

void listprintr(t_list *lst)
{
	t_list *p;
	p = lst;
	while (p->next != NULL)
	  p = p->next;  // переход к концу списка
	while (p != NULL) // условие окончания обхода
	{
		printf("%s\n", p->content); // вывод значения элемента p
		p = p->prev; // переход к предыдущему узлу
	}
}

int					main()
{
	t_list		*lst;
	
	lst = (t_list*)malloc(sizeof(t_list));
	init(lst, "fuck it");
	addelem(lst, "hello there");
	addelem(lst, "third");
	listprint(lst);
	listprintr(lst);
}