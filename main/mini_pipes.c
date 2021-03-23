/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:05:16 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/23 22:24:08 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			init_pipes(t_mini *s)
{
	int				i;

	i = -1;
	s->pipe.fd = (int **)malloc(sizeof(int *) * s->pipe.count_pipe);
	if (s->pipe.fd == NULL)
	{
		write(STDERR, "malloc was not allocated\n", 26);
		return (-1);
	}
	while (++i < s->pipe.count_pipe)
	{
		s->pipe.fd[i] = (int *)malloc(sizeof(int) * 2);
		if (s->pipe.fd[i] == NULL)
		{
			write(STDERR, "malloc was not allocated\n", 26);
			return (-1);
		}
	}
	i = -1;
	while (++i < s->pipe.count_pipe)
		pipe(s->pipe.fd[i]);
	return (0);
}

void				mini_pipes_child_p2(t_mini *s, int i)
{
	int				k;

	k = -1;
	if (s->array_fdin[i])
	{
		dup2(s->array_fdin[i], STDIN);
		close(s->array_fdin[i]);
	}
	else
		dup2(s->pipe.fd[i - 1][0], STDIN);
	if (s->array_fdout[i] > 1)
	{
		dup2(s->array_fdout[i], STDOUT);
		close(s->array_fdout[i]);
	}
	else if (i + 1 != s->pipe.count_commands)
		dup2(s->pipe.fd[i][1], STDOUT);
	while (++k < s->pipe.count_pipe)
	{
		close(s->pipe.fd[k][1]);
		if (k != 0 && i + 1 != s->pipe.count_commands)
			close(s->pipe.fd[k][0]);
	}
}

void				mini_pipes_child_p1(t_mini *s, int i)
{
	int				k;

	k = 0;
	if (s->array_fdin[i])
	{
		dup2(s->array_fdin[i], STDIN);
		close(s->array_fdin[i]);
	}
	if (s->array_fdout[i] > 1)
	{
		dup2(s->array_fdout[i], STDOUT);
		close(s->array_fdout[i]);
	}
	else
		dup2(s->pipe.fd[i][1], STDOUT);
	while (k < s->pipe.count_pipe)
	{
		close(s->pipe.fd[k][1]);
		if (k != 0)
			close(s->pipe.fd[k][0]);
		k++;
	}
}

void				mini_pipes_p2(t_mini *s)
{
	int				j;
	int				status;

	j = -1;
	status = 1;
	while (++j < s->pipe.count_pipe)
	{
		close(s->pipe.fd[j][0]);
		close(s->pipe.fd[j][1]);
		free(s->pipe.fd[j]);
	}
	free(s->pipe.fd);
	s->pipe.fd = NULL;
	j = -1;
	while (++j < s->pipe.count_commands)
		wait(NULL);
}

void				mini_pipes(t_mini *s, char ***arr)
{
	int				i;
	int				res;

	i = -1;
	init_pipes(s);
	while (++i < s->pipe.count_commands)
	{
		res = mini_bin_p1(s, arr[i][0], i);
		g_sig.pid = fork();
		if (g_sig.pid < 0)
			exit(127);
		else if (g_sig.pid == 0)
		{
			if (i == 0)
				mini_pipes_child_p1(s, i);
			else
				mini_pipes_child_p2(s, i);
			if (execve(s->var.bin, arr[i], s->env) == -1)
				write(2, strerror(errno), ft_strlen(strerror(errno)));
			exit(1);
		}
		if (res)
			ft_memdel_1d(s->var.bin);
	}
	mini_pipes_p2(s);
}
