/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:29:05 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/12 19:34:04 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_init(t_mini *s)
{
	s->arg = NULL;
	s->env = NULL;
	s->tmp = NULL;
	s->var.bin = NULL;
}

static void		mini_echo(char **s)
{
	int			i;

	i = 0;
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

static void		mini_pwd(t_mini	*s)
{
	char		*s1;

	s1 = NULL;
	s1 = malloc(1000);
	getcwd(s1, 100);
	write(1, s1, ft_strlen(s1));
	write(1, "\n", 1);
	ft_memdel(s1);
}

static void		mini_exit(char **s)
{

	write(1, s[0], ft_strlen(s[0]));
	write(1, "\n", 1);
	exit (0);

}

static void		mini_cd(t_mini *s)
{
	int			res;

	res = 0;
	res = chdir(s->arg[1]);
	if (res == -1)
	{
		write(1, "cd: ", 4);
		write(1, s->arg[1], ft_strlen(s->arg[1]));
		write(1, ": No such file or directory\n", 28);
	}

}

static void		mini_env(t_mini *s)
{
	
	int			i;

	i = 0;
	if (s->arg[1])
	{
		write(1, "env: ", 5);
		write(1, s->arg[1], ft_strlen(s->arg[1]));
		write(1, ": No such file or directory\n", 28);
	}
	else
		while (s->env[i] != NULL)
		{
			write(1, s->env[i], ft_strlen(s->env[i]));
			write(1, "\n", 1);
			i++;
		}
}

static void		mini_export(t_mini *s)
{
	
	int			i;

	i = 0;
	if (!(s->arg[1]))
		while (s->env[i] != NULL)
		{
			write(1, "declare -x ", 11);
			write(1, s->env[i], ft_strlen(s->env[i]));
			write(1, "\n", 1);
			i++;
		}
}

static void		sort_ft(t_mini	*s, char **env1)
{
	s->env = env1;
	if (ft_strcmp(s->arg[0], "echo") == 0)
		mini_echo(s->arg);
	else if (ft_strcmp(s->arg[0], "pwd") == 0)
		mini_pwd(s);
	else if (ft_strcmp(s->arg[0], "exit") == 0)
		mini_exit(s->arg);
	else if (ft_strcmp(s->arg[0], "cd") == 0)
		mini_cd(s);
	else if (ft_strcmp(s->arg[0], "env") == 0)
		mini_env(s);
	else if (ft_strcmp(s->arg[0], "export") == 0)
		mini_export(s);
	else
		mini_bin(s);
	ft_memdel_arr((void**)s->arg);
}

int			main(int ac, char **av, char **env1)
{
	t_mini	s;
	char	*line;
	int		status = 1;

	ft_init(&s);
	while (status)
	{
		write(1, "minishell$ ", 11);
		status = get_next_line(&line);
		s.arg = ft_split(line, ' ');
		free(line);
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