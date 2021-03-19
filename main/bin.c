/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:36:22 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/19 14:57:34 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void			ft_list_to_2d(t_mini *s)
{
	t_mass			*tmp;
	char			*line;
	int				i = 0;

	tmp = s->head;
	while (tmp != NULL)
	{
		s->env[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	while (s->env[i])
	{
		s->env[i] = NULL;
		i++;
	}
}

int					magic_box(t_mini *s, char *dir, char *exec)
{
	DIR				*folder;
	struct dirent	*command;
	char			*line = NULL;

	folder = opendir(dir);
	if (folder == NULL)
	{
		return (-10);
		// write(1, "error\n", 6);
		// exit (127);
	}
	while ((command = readdir(folder)))
	{
		if (ft_strcmp(command->d_name, exec) == 0)
		{
			s->var.count_bin++;
			line = ft_strjoin(dir, "/");
			s->var.bin = ft_strjoin(line, exec);
			ft_memdel_1d(line);
		}
	}
	closedir(folder);
	return (0);
}

int				absolute_path(t_mini *s, char *bin, char *exec)
{
	int			length_dir;
	int			length_com;

	if (ft_strncmp(bin, exec, ft_strlen(bin)) == 0)
		s->var.count_bin++; // we have a right directory
	if (s->var.count_bin == 2)
	{
		length_com = ft_strlen(exec);
		length_dir = ft_strlen(bin);
		length_dir++;
		if (length_com > length_dir)
		{
			s->var.count_bin++;
			magic_box(s, bin, exec + length_dir);
		}
	}
	return (s->var.count_bin);
}

char				**exec_bin_2(t_mini *s, char **bin, char *exec)
{
	// 
	return (bin);
}

int					exec_bin_1(t_mini *s, char *exec)
{
	int			i = 0;
	char		**bin;
	char		*path;
	t_mass		*tmp;

	tmp = s->head;
	while (tmp != NULL && ft_strncmp(tmp->content, "PATH=", 5) != 0)
		tmp = tmp->next;
	if (ft_strncmp(exec,  s->av, ft_strlen(s->av)) == 0) //ft_strncmp(exec, s->av + 2, ft_strlen(s->av + 2)) == 0 || 
	{
		// if (s->var.path == NULL)
		// 	s->var.bin = ft_strjoin(s->head_local->content, s->av);
		// else
			s->var.bin = s->av;
		ft_list_to_2d(s);
		ft_memdel_1d(s->var.path);
		return 0;
	}
	else if (exec[0] == '.' && exec[1] == '/')
	{
		s->var.bin = exec;
		return 0;
	}
	else if (tmp == NULL)
	{
		if (exec[0] == '/')
			bin = ft_split(s->var.path, ':');
		else
			return 1;
	}
	else
		bin = ft_split(tmp->content + 5, ':');
	if (exec[0] == '/')
		s->var.count_bin = 1;
	else
		s->var.count_bin = 5;
	while (bin[i]) //bin[i + 3]
	{ //make it finish when command is found
		// printf("%s\n", bin[i]);
		if (s->var.count_bin == 1)
			absolute_path(s, bin[i], exec);
		else
			magic_box(s, bin[i], exec);
		i++;
	}
	ft_memdel_2d((void**)bin);
	return (s->var.count_bin);
}

void				bin_error(t_mini *s, char *exec, int res)
{
	if (res == 4 || res == 6 || res == 0)
	{
		g_sig.exit_status = 0;
		return ;
	}
	else
	{
		write(1, "bash: ", 6);
		write(1, exec, ft_strlen(exec));
		if (res == 1 || res == 3)
		{
			write(STDERR, ": No such file or directory\n", 28); // 127
			g_sig.exit_status = 127;
		}
		else if (res == 2)
		{
			write(STDERR, ": is a directory\n", 17); // 126
			g_sig.exit_status = 126;
		}
		else if (res == 5)
		{
			write(STDERR, ": command not found\n", 20); // 127
			g_sig.exit_status = 127;
		}
	}
}

int					exec_bin(t_mini *s, char **arr, char *exec)
{
	// pid_t			pid;
	int				res = 0;
	char			*bin = NULL;

	res = exec_bin_1(s, exec);
	g_sig.pid = fork();
	if (g_sig.pid < 0)
	{
		write(STDERR, "error\n", 6);
		exit (127);
	}
	else if (g_sig.pid == 0)
	{
		printf("fdin: %d\n", s->fdin);
		printf("fdout: %d\n", s->fdout);
		if (s->from_file)
		{
			dup2(s->fdin, STDIN);
		
		}
		else
		if (s->in_file)
		{
			dup2(s->fdout, STDOUT);
			
		}
		execve(s->var.bin, arr, s->env);
		exit (1);
	}
	else
	{
		// we need to use waitpid instead of wait
		wait(NULL);
	}
	if (res)
		ft_memdel_1d(s->var.bin);
	bin_error(s, exec, res);
	return (0);
}