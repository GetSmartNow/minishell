/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:29:05 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/17 00:33:54 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_init(t_mini *s)
{
	s->arg = NULL;
	s->env = NULL;
	s->tmp = NULL;
	s->var.bin = NULL;
}

static void		sort_ft(t_mini	*s, char **env1)
{
	s->env = env1;
	if (ft_strcmp(s->arg[0], "echo") == 0)
		mini_echo(s->arg);
	else if (ft_strcmp(s->arg[0], "pwd") == 0)
		mini_pwd(s);
	else if (ft_strcmp(s->arg[0], "exit") == 0)
		mini_exit(s->arg);
	else if (ft_strcmp(s->arg[0], "cd") == 0)
		mini_cd(s);
	else if (ft_strcmp(s->arg[0], "env") == 0)
		mini_env(s);
	else if (ft_strcmp(s->arg[0], "export") == 0)
		mini_export(s);
	else
		mini_bin(s);
	ft_memdel_2d((void**)s->arg);
}

static int		init_list(t_mini *s, char **env)
{
	t_mass		*tmp = NULL;
	t_mass		*tmp1 = NULL;
	char		*line = NULL;
	int			i = 0;

	s->head = NULL;
	while (env[i] != NULL)
	{
		line = ft_strdup(env[i]);
		my_lstadd_back(&s->head, my_lstnew(line));
		i++;
	}
	// tmp = s->head;
	// while (tmp->next != NULL)
	// {
	// 	printf("|%s|\n", tmp->content);
	// 	tmp = tmp->next;
	// }
	// printf("|%s|\n", s->head->content);
	return (0);
}

int			main(int ac, char **av, char **env1)
{
	t_mini	s;
	char	*line;
	int		status = 1;
	int		i = 0;
	int		j = 0;

	s.mass3d = (char ***)malloc(sizeof(char) * 10);
	ft_init(&s);
	init_list(&s, env1);
	while (status)
	{
		ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDOUT);
		status = get_next_line(&line);
		s.pipes = ft_split(line, '|');
		// s.arg = ft_split(line, ' ');
		while (s.pipes[i])
		{
			printf("p|%s|\n", s.pipes[i]);
			s.mass3d[i] = ft_split(s.pipes[i], ' ');
			i++;
		}
		i = 0;
		// printf("a|%s|\n", s.mass3d[i][j]);
		while (s.mass3d[i])
		{
			j = 0;
			while(s.mass3d[i][j])
			{
				printf("a|%s|\n", s.mass3d[i][j]);
				j++;
			}
			i++;
		}
		free(line);
		// ft_memdel_3d((void***)s.mass3d);
		// sort_ft(&s, env1);
	}
	return (0);
}






































