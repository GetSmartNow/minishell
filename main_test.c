/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:29:05 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/15 19:45:20 by ctycho           ###   ########.fr       */
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

static void		mini_exit(char **s)
{

	write(1, s[0], ft_strlen(s[0]));
	write(1, "\n", 1);
	exit (0);

}

static void		mini_env(t_mini *s)
{
	t_mass		*tmp;
	int			i;

	i = 0;
	if (s->arg[1])
	{
		write(1, "env: ", 5);
		write(1, s->arg[1], ft_strlen(s->arg[1]));
		write(1, ": No such file or directory\n", 28);
	}
	else
	{
		tmp = s->head;
		while (s->env[i] != NULL)
		{
			write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
			tmp = tmp->next;
			i++;
		}
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

static int		init_list(t_mini *s, char **env)
{
	t_mass		*tmp = NULL;
	t_mass		*tmp1 = NULL;
	char		*line = NULL;
	int			i = 0;

	s->head = NULL;
	// tmp = s->head;
	while (env[i] != NULL)
	{
		line = ft_strdup(env[i]);
		my_lstadd_back(&s->head, my_lstnew(line));
		i++;
	}
	// tmp = s->head;
	// while (tmp->next != NULL)
	// {
	// 	printf("|%s|\n", tmp->content);
	// 	tmp = tmp->next;
	// }
	// printf("|%s|\n", s->head->content);
	return (0);
}

int			main(int ac, char **av, char **env1)
{
	t_mini	s;
	char	*line;
	int		status = 1;

	ft_init(&s);
	init_list(&s, env1);
	// env_init(env1);
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






































