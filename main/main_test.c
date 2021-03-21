/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:35:14 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/21 14:59:35 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		ft_init_before_loop(t_mini *s, char *av)
{
	g_sig.exit_status = 0;
	s->av = av;
	s->var.pwd = 0;
	s->exit = 0;
	s->var.path = NULL;
}

static void		ft_init_in_loop(t_mini *s)
{
	//мб перенести в место выделения
	//int			i = 0;
	//int			j = 0;
	//while (s->mass3d[i])
	//{
	//	j = 0;
	//	while (s->mass3d[i][j])
	//	{
	//		s->mass3d[i][j] = NULL;
	//		j++;
	//	}
	//	i++;
	//}
	s->fdin = 0;
	s->fdout = 0;
	s->in_file = NULL;
	s->from_file = NULL;
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

static void		exit_code(t_mini *s) // signal goes to all proceses
{
	char		*nbr;

	nbr = ft_itoa(g_sig.exit_status);
	write(1, "bash: ", 6);
	write(1, nbr, ft_strlen(nbr));
	write(1, ": command not found\n", 20);
	ft_memdel_1d(nbr);
	g_sig.exit_status = 127;
}

void		sort_ft(t_mini *s, char **env1)
{
	s->env = env1;
	if (ft_strcmp(s->mass3d[0][0], "$?") == 0) // this thins is temporary here
		exit_code(s);
	else if (s->pipe.count_pipe != 0) 
		mini_pipes(s);
	else if (ft_strcmp(s->mass3d[0][0], "echo") == 0 || ft_strcmp(s->mass3d[0][0], "ECHO") == 0)
		mini_echo(s->mass3d[0], s);
	else if (ft_strcmp(s->mass3d[0][0], "pwd") == 0 || ft_strcmp(s->mass3d[0][0], "PWD") == 0)
		mini_pwd(s);
	else if (ft_strcmp(s->mass3d[0][0], "exit") == 0 || ft_strcmp(s->mass3d[0][0], "EXIT") == 0)
		mini_exit(s, s->mass3d[0][0], s->mass3d[0][1]);
	else if (ft_strcmp(s->mass3d[0][0], "cd") == 0 || ft_strcmp(s->mass3d[0][0], "CD") == 0)
		mini_cd(s, s->mass3d[0][0], s->mass3d[0][1]);
	else if (ft_strcmp(s->mass3d[0][0], "env") == 0  || ft_strcmp(s->mass3d[0][0], "ENV") == 0)
		mini_env(s);
	else if (ft_strcmp(s->mass3d[0][0], "export") == 0 || ft_strcmp(s->mass3d[0][0], "EXPORT") == 0)
		mini_export(s);
	else if (ft_strcmp(s->mass3d[0][0], "unset") == 0 || ft_strcmp(s->mass3d[0][0], "UNSET") == 0)
		mini_unset(s);
	else
		exec_bin(s, s->mass3d[0], s->mass3d[0][0]);
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
	// ft_list_sort(&s->head_x);
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
	// ft_list_sort(&s->head);
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_mini	s;
	char	*line = NULL;
	int		status = 1;
	int		i = 0;
	int		j = 0;
	int 	res = 0;

	s.av = av[0];
	s.var.pwd = 0;
	s.exit = 0;
	g_sig.exit_status = 0;
	s.var.path = NULL;
	init_list(&s, env);
	init_list_x(&s, env);
	ft_shlvl(&s);
	get_pwd(&s);
	while (status && s.exit == 0)
	{
		init_signal();
		signal(SIGINT, &sig_int); // Register signal handler
		signal(SIGQUIT, &sig_quit);
		ft_init_in_loop(&s);
		ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDOUT);
		status = get_next_line(&line);
		if (status)
		{
			ft_parser(&s, line, env);
			ft_memdel_1d(line);
		}
	}
	return (g_sig.exit_status);
}


/* int			main(int ac, char **av, char **env)
{
	t_mini	s;
	char	*line = NULL;
	int		status = 1;
	int		i = 0;
	int 	res = 0;

	ft_init_before_loop(&s, av[0]);
	init_list(&s, env);
	init_list_x(&s, env);
	ft_shlvl(&s);
	get_pwd(&s);
	while (status && s.exit == 0)
	{
		init_signal();
		signal(SIGINT, &sig_int); // Register signal handler
		signal(SIGQUIT, &sig_quit);
		ft_init_in_loop(&s);
		ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDOUT);
		status = get_next_line(&line);
		if (status)
		{
			ft_parser(&s, line, env);
			ft_memdel_1d(line);
		}
	}
	return (g_sig.exit_status);
}
