/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:46:08 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/19 18:34:56 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				mini_pwd_1(t_mini *s)
{
	t_mass			*tmp;
	char			*line;

	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
		{
			free(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			tmp->content = ft_strjoin("PWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen("PWD=")) == 0)
		{
			free(tmp->content);
			line = malloc(1000);
			getcwd(line, 100);
			tmp->content = ft_strjoin("PWD=", line);
			ft_memdel_1d(line);
		}
		tmp = tmp->next;
	}
}

void				mini_pwd(t_mini	*s)
{
	char			*s1;

	s1 = NULL;
	s1 = malloc(1000);
	getcwd(s1, 100);
	write(s->fdout, s1, ft_strlen(s1));
	write(s->fdout, "\n", 1);
	ft_memdel_1d(s1);
}