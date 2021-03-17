/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:53:47 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/17 11:22:10 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			get_pwd(t_mini	*s)
{
	t_mass		*tmp;
	char		*line = NULL;
	char		*free_str = NULL;
	int			flag = 0;

	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
		{
			flag = 1;
			ft_memdel_1d(tmp->content);
			// ft_bzero(tmp->content, ft_strlen(tmp->content));
			line = malloc(1000);
			getcwd(line, 100);
			tmp->content = ft_strjoin("PWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = malloc(1000);
		getcwd(line, 100);
		line = ft_strjoin("PWD=", line);
		my_lstadd_back(&s->head, my_lstnew(line));
	}
	flag = 0;
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
		{
			flag = 1;
			ft_memdel_1d(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			free_str = ft_strjoin_free("PWD=", line, line);
			tmp->content = put_quotes(free_str);
			ft_memdel_1d(free_str);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = malloc(1000);
		getcwd(line, 100);
		free_str = ft_strjoin_free("PWD=", line, line);
		ft_memdel_1d(line);
		free_str = put_quotes(free_str);
		my_lstadd_back(&s->head_x, my_lstnew(free_str));
	}
}