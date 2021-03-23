/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:36:22 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/23 22:23:52 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					exec_path_p2(t_mini *s, char *exec, t_mass *tmp, int i)
{
	char		**bin;

	if (tmp == NULL)
	{
		if (exec[0] == '/')
			bin = ft_split(s->var.path, ':');
		else
			return (1);
	}
	else
		bin = ft_split(tmp->content + 5, ':');
	if (exec[0] == '/')
		s->var.count_bin = 1;
	else
		s->var.count_bin = 5;
	while (bin[i])
	{
		if (s->var.count_bin == 1)
			absolute_path(s, bin[i], exec);
		else
			magic_box(s, bin[i], exec);
		i++;
	}
	ft_memdel_2d((void**)bin);
	return (s->var.count_bin);
}

int					exec_path_p1(t_mini *s, char *exec)
{
	t_mass		*tmp;
	int			res;
	int			i;

	i = 0;
	tmp = s->head;
	while (tmp != NULL && ft_strncmp(tmp->content, "PATH=", 5) != 0)
		tmp = tmp->next;
	if (ft_strncmp(exec, s->av, ft_strlen(s->av)) == 0)
	{
		s->var.bin = s->av;
		ft_list_to_2d(s);
		ft_memdel_1d(s->var.path);
		return (0);
	}
	else if (exec == NULL)
		return (-1);
	else if (exec[0] == '.' && exec[1] == '/')
	{
		s->var.bin = exec;
		return (0);
	}
	else
		res = exec_path_p2(s, exec, tmp, i);
	return (res);
}

int					exec_bin_child(t_mini *s, char **arr)
{
	if (s->array_fdin[0])
	{
		dup2(s->array_fdin[0], STDIN);
		close(s->array_fdin[0]);
	}
	if (s->array_fdout[0] > 1)
	{
		dup2(s->array_fdout[0], STDOUT);
		close(s->array_fdout[0]);
	}
	execve(s->var.bin, arr, s->env);
	exit(1);
}

int					exec_bin(t_mini *s, char **arr, char *exec)
{
	int				res;
	int				status;

	status = 1;
	res = exec_path_p1(s, exec);
	if (ft_strcmp(s->var.bin, "cat") == 0 ||\
	ft_strcmp(s->var.bin, "/bin/cat") == 0)
		g_sigcat = 1;
	g_sig.pid = fork();
	if (g_sig.pid < 0)
		exit(127);
	else if (g_sig.pid == 0)
		exec_bin_child(s, arr);
	waitpid(g_sig.pid, &status, 0);
	if (res)
		ft_memdel_1d(s->var.bin);
	bin_error(exec, res, status);
	if (status == 2)
		g_sig.exit_status = 130;
	else if (status == 3)
		g_sig.exit_status = 131;
	else if (status != 0 && status != 256)
		g_sig.exit_status = status >> 8;
	return (0);
}
