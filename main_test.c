/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:35:14 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/05 16:54:46 by mvernius         ###   ########.fr       */
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

static void		sort_ft(t_mini *s, char **env1)
{
	s->env = env1;
	if (s->pipe.count_pipe != 0)
		mini_pipes(s);
	else if (ft_strcmp(s->mass3d[0][0], "echo") == 0)
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
	else if (ft_strcmp(s->mass3d[0][0], "unset") == 0)
		mini_unset(s);
	else
		mini_bin(s);
}

static int		init_list_x(t_mini *s, char **env)
{
	t_mass		*tmp = NULL;
	t_mass		*tmp1 = NULL;
	char		*line = NULL;
	int			i = 0;

	s->head_x = NULL; //export
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
	ft_list_sort(&s->head_x);
	return (0);
}

static int		init_list(t_mini *s, char **env)
{
	t_mass		*tmp = NULL;
	t_mass		*tmp1 = NULL;
	char		*line = NULL;
	int			i = 0;

	s->head = NULL; //env
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")) != 0)
		{
			line = ft_strdup(env[i]);
			my_lstadd_back(&s->head, my_lstnew(line));
		}
		i++;
	}
	ft_list_sort(&s->head);
	return (0);
}

static int		check_pipes(t_mini *s, char *line)
{
	int			i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '|')
			s->pipe.count_pipe++;
		i++;
	}
	return (i);
}

static int				check_line(t_mini *s, char *line)
{
	int					i = 0;
	int					res = 0;

	res = check_pipes(s, line);
	if (res == 0)
		return (-1);
	if (s->pipe.count_pipe != 0)
	{
		s->div_pipe = ft_split(line, '|');
		while (s->div_pipe[i])
		{
			s->mass3d[i] = ft_split(s->div_pipe[i], ' ');
			s->pipe.count_commands++;
			i++;
		}
		ft_memdel_2d((void**)s->div_pipe);
	}
	else
		s->mass3d[i] = ft_split(line, ' ');
	return (res);
}

int			main(int ac, char **av, char **env)
{
	t_mini	s;
	char	*line;
	int		status = 1;
	int		i = 0;
	int		j = 0;
	int 	res = 0;

	s.mass3d = (char ***)ft_calloc(sizeof(char **), 100);
	s.var.pwd = 0;
	init_list(&s, env);
	init_list_x(&s, env);
	ft_shlvl(&s);
	get_pwd(&s);
	while (status)
	{
		ft_init(&s);
		ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDOUT);
		status = get_next_line(&line);
		// add lopp until ';'
		//separate commands ; should return command array
		//then every command in array should be checked by check_line;
		char **sep_commands = ft_split(line, ';');
		while (*sep_commands)
		{
			printf("str: \"%s\"\n", *sep_commands);
			res = check_line(&s, *sep_commands);
			if (res > 0)
				sort_ft(&s, env);
			sep_commands++;
		}
		//res = check_line(&s, line);
		//free(line);
		//if (res > 0)
		//	sort_ft(&s, env);
	}
	return (0);
}






































