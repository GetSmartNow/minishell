/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_p2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:47:41 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/23 16:48:01 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				get_home(t_mini *s)
{
	t_mass			*tmp;
	char			*line;

	line = NULL;
	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "HOME=", ft_strlen("HOME=")) == 0)
		{
			line = ft_strdup(tmp->content + 5);
		}
		tmp = tmp->next;
	}
	chdir(line);
	ft_memdel_1d(line);
}
