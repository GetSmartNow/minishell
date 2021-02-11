/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:29:05 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/10 20:04:41 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		mini_echo(char **s)
{
	int			i = 0;

	if (s[1] == NULL)
		write(1, "\n", 1);
	else if (ft_strcmp(s[1], "-n") == 0)
	{
		i = 1;
		while (s[++i])
		{
			write(1, s[i], ft_strlen(s[i]));
			s[i + 1] != NULL ? write(1, " ", 1) : 0;
		}
	}
	else
	{
		while (s[++i])
		{
			write(1, s[i], ft_strlen(s[i]));
			s[i + 1] != NULL ? write(1, " ", 1) : 0;
		}
		write(1, "\n", 1);
	}
}

static void		mini_pwd(char **s)
{
	char		*s1;

	s1 = NULL;
	s1 = malloc(1000);
	getcwd(s1, 100);
	write(1, s1, ft_strlen(s1));
	write(1, "\n", 1);
}

static void		mini_exit(char **s)
{

	write(1, s[0], ft_strlen(s[0]));
	write(1, "\n", 1);
	exit (0);

}

static char		*join_dir(char **s)
{
	char		*dir;
	int			i = 5;
	int			j = 0;

	dir = (char *)malloc(sizeof(char) * 50);
	dir[0] = '/';
	dir[1] = 'b';
	dir[2] = 'i';
	dir[3] = 'n';
	dir[4] = '/';
	// printf("s:|%s|\n", s[0]);
	// dir = ft_strjoin(dir, s[0]);
	while (s[0][j])
	{
		dir[i++] = s[0][j++];
	}
	dir[i] = '\0';
	return (dir);
}

static int		mini_env(char **s, char **env)
{
	pid_t		pid;
	int			i = 0;
	char		*dir;
	int			status;

	for(int p = 0; p < 1; p++)
	{
		dir = join_dir(s);
		// printf("|%s|\n", dir);
		pid = fork();
		// printf("|%s|\n", s[0]);
		if (pid < 0)
		{
			write(1, "error\n", 6);
			exit (127);
		}
		else if (pid == 0)
		{
			execve(dir, s, env);
			exit (1);
		}
	}
	if (waitpid(pid, &status, 0) > 0)
	{
		return (status);
	}
	return (0);
}

static void		sort_ft(char **s, char **env)
{
	if (ft_strcmp(s[0], "echo") == 0)
		mini_echo(s);
	else if (ft_strcmp(s[0], "pwd") == 0)
		mini_pwd(s);
	else if (ft_strcmp(s[0], "exit") == 0)
		mini_exit(s);
	else
		mini_env(s, env);
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	char	**s;
	int		status = 1;
	
	// printf("env |%s|\n", env[0]);
	// printf("env1 |%s|\n", env[1]);
	while (status)
	{
		write(1, "minishell$ ", 11);
		status = get_next_line(&line);
		s = ft_split(line, ' ');
		// printf("|%s|\n", s[0]);
		sort_ft(s, env);
	}
	return (0);
}
