/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:17:01 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/23 22:21:20 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_run_command_elems(t_mini *s, int iter_pipes)
{
	int		iter_elems;
	char	*tmp;

	s->command_elems = ft_split_new((s->pipes)[iter_pipes], ' ');
	if (NULL == s->command_elems)
		paste_error("malloc error\n", s);
	iter_elems = 0;
	while ((s->command_elems)[iter_elems])
	{
		tmp = (s->command_elems)[iter_elems];
		(s->command_elems)[iter_elems] =
			make_substitute((s->command_elems)[iter_elems],
			&(s->head), iter_elems, s);
		ft_memdel_1d((void *)tmp);
		iter_elems++;
	}
}

void	run_pipes(t_mini *s)
{
	int		iter_pipes;

	iter_pipes = 0;
	while ((s->pipes)[iter_pipes])
	{
		s->pipes[iter_pipes] = extract_command(s->pipes[iter_pipes], '>', s);
		if (NULL == s->pipes[iter_pipes])
			paste_error("malloc error\n", s);
		s->pipes[iter_pipes] = extract_command(s->pipes[iter_pipes], '<', s);
		if (NULL == s->pipes[iter_pipes])
			paste_error("malloc error\n", s);
		make_run_command_elems(s, iter_pipes);
		(s->mass3d)[iter_pipes] = s->command_elems;
		iter_pipes++;
	}
}

void	prepare_for_pipes(t_mini *s, int iter_commands)
{
	s->pipes = ft_split_new((s->commands)[iter_commands], '|');
	if (NULL == s->pipes)
		paste_error("malloc error\n", s);
	s->pipe.count_pipe = ft_arrlen(s->pipes) - 1;
	s->pipe.count_commands = s->pipe.count_pipe + 1;
	s->mass3d = (char ***)malloc((s->pipe.count_commands + 1)
		* sizeof(char **));
	if (NULL == s->mass3d)
		paste_error("malloc error\n", s);
	s->array_fdin = (int *)malloc(ft_arrlen(s->pipes) * sizeof(int));
	if (NULL == s->array_fdin)
		paste_error("malloc error\n", s);
	s->array_fdout = (int *)malloc(ft_arrlen(s->pipes) * sizeof(int));
	if (NULL == s->array_fdout)
		paste_error("malloc error\n", s);
}

void	prepare_commands(t_mini *s, const char *line, char **env)
{
	int iter_commands;

	s->commands = ft_split_new(line, ';');
	if (NULL == s->commands)
		paste_error("malloc error\n", s);
	iter_commands = 0;
	while ((s->commands)[iter_commands])
	{
		if (s->err_status == 0)
		{
			prepare_for_pipes(s, iter_commands);
			ft_sort_pipes(s);
			run_pipes(s);
			if (s->err_status)
				print_error(s);
			else if (ft_strlen_modif((s->commands)[iter_commands]) > 0)
				sort_ft(s, env);
			iter_commands++;
			free_command(s);
		}
	}
}

void	ft_parser(t_mini *s, char *line, char **env)
{
	init_err_info(s);
	run_checks(line, s);
	if (s->err_status == 0)
	{
		prepare_commands(s, line, env);
		ft_memdel_2d((void **)s->commands);
		ft_memdel_1d(s->err_message);
	}
	else
		print_error(s);
}
