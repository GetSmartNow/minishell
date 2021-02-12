/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:29:05 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/12 14:05:33 by ctycho           ###   ########.fr       */
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

static char		*join_dir(t_mini *s)
{
	char		**bin = NULL;
	int			i = 0;

	s->tmp = NULL;
	while (ft_strncmp(s->env[i], "PATH=", 5) != 0)
		i++;
	printf("|%s|\n", s->env[i]);
	bin = ft_split(s->env[i], ':');
	printf("|%s|\n", bin[0]);
	s->tmp = bin[0];
	s->tmp = ft_strnstr(s->tmp, "/bin", ft_strlen(s->tmp));
	s->tmp = ft_strjoin(s->tmp, "/");
	i = 0;
	while (bin[i] != NULL)
	{
		free(bin[i]);
		i++;
		// printf("|%s|\n", bin[i]);
	}
	return (s->tmp);
}

static int		mini_env(t_mini *s)
{
	DIR				*folder;
	struct dirent	*command;
	pid_t			pid;
	int				i = 0;
	int				status;
	char			*bin = NULL;

	bin = join_dir(s);
	free(s->tmp);
	folder = opendir(bin);
	if (folder == NULL)
	{
		write(1, "error\n", 6);
		exit (127);
	}
	while ((command = readdir(folder)))
	{
		if (ft_strcmp(command->d_name, s->arg[0]) == 0)
		{
			bin = ft_strjoin(bin, s->arg[0]);
			free(s->arg[0]);
		}
	}
	closedir(folder);
	printf("|%s|\n", bin);
	pid = fork();
	if (pid < 0)
	{
		write(1, "error\n", 6);
		exit (127);
	}
	else if (pid == 0)
	{
		execve(bin, s->arg, s->env);
		free(bin);
		exit (1);
	}
	free(bin);
	if (waitpid(pid, &status, 0) > 0)
	{
		return (status);
	}
	return (0);
}

static void		sort_ft(t_mini	*s, char **env1)
{
	s->env = env1;
	if (ft_strcmp(s->arg[0], "echo") == 0)
		mini_echo(s->arg);
	else if (ft_strcmp(s->arg[0], "pwd") == 0)
		mini_pwd(s->arg);
	else if (ft_strcmp(s->arg[0], "exit") == 0)
		mini_exit(s->arg);
	else
		mini_env(s);
}

int			main(int ac, char **av, char **env1)
{
	t_mini	s;
	char	*line;
	int		status = 1;
	
	// env_init(env);

	// printf("env |%s|\n", env1->content);
	while (status)
	{
		write(1, "minishell$ ", 11);
		status = get_next_line(&line);
		s.arg = ft_split(line, ' ');
		free(line);
		// printf("|%s|\n", s[0]);
		sort_ft(&s, env1);
	}
	return (0);
}






































// static void		env_init(char **env_array)
// {
// 	t_list		*env1;
// 	t_list		*tmp;
// 	int			i = 0;

// 	// if (!(env = malloc(sizeof(t_env))))
// 	// 	return ;
// 	ft_lstnew(env_array[i]);
// 	tmp = env1;
// 	while (env_array[i++] != NULL)
// 	{
// 		ft_lstadd_back(&tmp, ft_lstnew(env_array[i]));
// 		// printf("env |%s|\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// }