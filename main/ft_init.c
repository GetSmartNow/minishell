/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:27:47 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/22 21:02:06 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			ft_init_before_loop(t_mini *s, char *av)
{
	g_sig.exit_status = 0;
	s->av = av;
	s->var.pwd = 0;
	s->exit = 0;
	s->var.path = NULL;
}

void			ft_init_in_loop(t_mini *s)
{
	s->fdin = 0;
	s->fdout = 0;
	s->free_line = NULL;
	s->env = NULL;
	s->tmp = NULL;
	s->var.bin = NULL;
	s->var.oldpwd = NULL;
	s->var.count_bin = 0;
	s->div_pipe = NULL;
	s->pipe.count_commands = 0;
	s->pipe.count_pipe = 0;
	s->div_pipe = NULL;
}

int				init_list_x(t_mini *s, char **env)
{
	t_mass		*tmp = NULL;
	t_mass		*tmp1 = NULL;
	char		*line = NULL;
	int			i = 0;

	s->head_x = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")) != 0)
		{
			line = put_quotes(env[i]);
			my_lstadd_back(&s->head_x, my_lstnew(line));
		}
		i++;
	}
	line = ft_strdup("OLDPWD");
	my_lstadd_back(&s->head_x, my_lstnew(line));
	return (0);
}

int				init_list(t_mini *s, char **env)
{
	t_mass		*tmp = NULL;
	t_mass		*tmp1 = NULL;
	char		*line = NULL;
	int			i = 0;

	s->head = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")) != 0)
		{
			line = ft_strdup(env[i]);
			my_lstadd_back(&s->head, my_lstnew(line));
		}
		i++;
	}
	return (0);
}
