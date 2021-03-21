/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:35:14 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/21 21:07:28 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int			main(int ac, char **av, char **env)
{
	t_mini	s;
	char	*line = NULL;
	int		status = 1;
	int		i = 0;
	int		j = 0;
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
		if (sigint == 1 && sigd == 1)
			ft_memdel_1d(line);
		else if (status)
		{
			ft_parser(&s, line, env);
			ft_memdel_1d(line);
		}
	}
	return (g_sig.exit_status);
}