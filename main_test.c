/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:29:05 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/21 00:38:05 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_init(t_mini *s)
{
	s->arg = NULL;
	s->env = NULL;
	s->tmp = NULL;
	s->var.bin = NULL;
	s->div_pipe = NULL;
	s->pipe.count_commands = 0;
	s->pipe.count_pipe = 0;
	s->div_pipe = NULL;
}

static void		sort_ft(t_mini	*s, char **env1)
{
	s->env = env1;
	// printf("|%s|\n", s->mass3d[0][0]);
	if (ft_strcmp(s->mass3d[0][0], "echo") == 0)
		mini_echo(s->mass3d[0]);
	else if (ft_strcmp(s->mass3d[0][0], "pwd") == 0)
		mini_pwd(s);
	else if (ft_strcmp(s->mass3d[0][0], "exit") == 0)
		mini_exit(s->mass3d[0]);
	else if (ft_strcmp(s->mass3d[0][0], "cd") == 0)
		mini_cd(s);
	else if (ft_strcmp(s->mass3d[0][0], "env") == 0)
		mini_env(s);
	else if (ft_strcmp(s->mass3d[0][0], "export") == 0)
		mini_export(s);
	else
		mini_pipes(s);
		// mini_bin(s);
}

static int		init_list_x(t_mini *s, char **env)
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
			line = ft_strdup(env[i]);
			my_lstadd_back(&s->head_x, my_lstnew(line));
		}
		i++;
	}
	return (0);
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
		if (ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")) != 0)
		{
			line = ft_strdup(env[i]);
			my_lstadd_back(&s->head, my_lstnew(line));
		}
		i++;
	}
	// tmp = s->head;
	// while (tmp != NULL)
	// {
	// 	// printf("|%s|\n", tmp->content);
	// 	write(1, tmp->content, ft_strlen(tmp->content));
	// 	write(1, "\n", 1);
	// 	tmp = tmp->next;
	// }
	// tmp = s->head;
	// while (tmp->next != NULL)
	//   tmp = tmp->next;  // переход к концу списка
	// while (tmp != NULL) // условие окончания обхода
	// {
	// 	printf("%s\n", tmp->content); // вывод значения элемента tmp
	// 	tmp = tmp->prev; // переход к предыдущему узлу
	// }
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_mini	s;
	char	*line;
	int		status = 1;
	int		i = 0;
	int		j = 0;

	s.mass3d = (char ***)malloc(sizeof(char) * 1000);
	init_list(&s, env);
	init_list_x(&s, env);
	while (status)
	{
		ft_init(&s);
		ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDOUT);
		status = get_next_line(&line);
		s.div_pipe = ft_split(line, '|');
		i = 0;
		while (s.div_pipe[i])
		{
			// printf("p|%s|\n", s.div_pipe[i]);
			s.mass3d[i] = ft_split(s.div_pipe[i], ' ');
			s.pipe.count_commands++;
			i++;
		}
		i = 0;
		// while (s.mass3d[i])
		// {
		// 	j = 0;
		// 	while(s.mass3d[i][j])
		// 	{
		// 		printf("a|%s|\n", s.mass3d[i][j]);
		// 		j++;
		// 	}
		// 	i++;
		// }
		// printf("|%d|\n", s.pipe.count_commands);
		free(line);
		sort_ft(&s, env);
		ft_memdel_2d((void**)s.div_pipe);
		i = 0;
		// while (s.mass3d[i])
		// {
		// 	write(1, "*", 1);
		// 	ft_memdel_2d((void**)s.mass3d[i]);
		// 	i++;
		// }
	}
	return (0);
}






































