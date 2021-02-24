/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:35:14 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/24 20:27:17 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_init(t_mini *s)
{
	s->arg = NULL;
	s->env = NULL;
	s->tmp = NULL;
	s->var.bin = NULL;
	s->div_pipe = NULL;
	s->pipe.count_commands = 0;
	s->pipe.count_pipe = 0;
	s->div_pipe = NULL;
}

static int			mini_atoi(char *line)
{
	int				i;
	int				res;
	
	i = 0;
	res = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			res = (res * 10) + (line[i] - 48);
			i++;
		}
		else
			i++;
	}
	return (res);
}

static int				check_shlvl(t_mini *s, char *line)
{
	int					i = 0;
	int					flag = 0;

	while (line[i] != '=')
		i++;
	printf("1|%c|\n", line[i]);
	i++;
	printf("2|%c|\n", line[i]);
	while (line[i] != '\0')
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			printf("3|%c|\n", line[i]);
			flag = 1;
		}
		else
		{
			printf("4|%c|\n", line[i]);
			return (2);
		}
		i++;
	}
	return (flag);
}

static void				ft_shlvl(t_mini *s, char **env)
{
	t_mass			*tmp;
	int				flag = 0;
	char			*line;

	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "SHLVL=", 6) == 0)
		{
			flag = check_shlvl(s, tmp->content);
			if (flag == 1)
			{
				s->var.shlvl = mini_atoi(tmp->content);
				s->var.shlvl++;
				printf("lvl = |%d|\n", s->var.shlvl);
				ft_bzero(tmp->content, ft_strlen(tmp->content));
				tmp->content = ft_strjoin("SHLVL=", ft_itoa(s->var.shlvl));
			}
			else if (flag == 2)
			{
				ft_bzero(tmp->content, ft_strlen(tmp->content));
				tmp->content = ft_strdup("SHLVL=1");
			}
			printf("flag = |%d|\n", flag);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		line = ft_strdup("SHLVL=1");
		my_lstadd_back(&s->head, my_lstnew(line));
	}
}

static void		sort_ft(t_mini *s, char **env1)
{
	s->env = env1;
	// printf("|%s|\n", s->mass3d[0][0]);
	if (ft_strcmp(s->mass3d[0][0], "echo") == 0)
	{
		mini_echo(s->mass3d[0]);
	}
	else if (ft_strcmp(s->mass3d[0][0], "pwd") == 0)
	{
		mini_pwd(s);
	}
	else if (ft_strcmp(s->mass3d[0][0], "exit") == 0)
		mini_exit(s->mass3d[0]);
	else if (ft_strcmp(s->mass3d[0][0], "cd") == 0)
		mini_cd(s);
	else if (ft_strcmp(s->mass3d[0][0], "env") == 0)
		mini_env(s);
	else if (ft_strcmp(s->mass3d[0][0], "export") == 0)
		mini_export(s);
	else if (ft_strcmp(s->mass3d[0][0], "unset") == 0)
		mini_unset(s);
	else
	{
		mini_pipes(s);
	}
}

static int		init_list_x(t_mini *s, char **env)
{
	t_mass		*tmp = NULL;
	t_mass		*tmp1 = NULL;
	char		*line = NULL;
	int			i = 0;

	s->head_x = NULL;
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
	ft_list_sort(&s->head_x, 0);
	return (0);
}

static int		init_list(t_mini *s, char **env)
{
	t_mass		*tmp = NULL;
	t_mass		*tmp1 = NULL;
	char		*line = NULL;
	int			i = 0;

	s->head = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")) != 0)
		{
			line = ft_strdup(env[i]);
			my_lstadd_back(&s->head, my_lstnew(line));
		}
		// if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		// {
		// 	// ft_bzero(env[i], ft_strlen(env[i]));
		// 	env[i] = NULL;
		// 	line = ft_strjoin("SHLVL=", mini_putnbr(s->var.shlvl));
		// 	my_lstadd_back(&s->head, my_lstnew(line));
		// }
		i++;
	}
	// tmp = s->head;
	// while (tmp != NULL)
	// {
	// 	if (ft_strncmp(tmp->content, "SHLVL=", 6) == 0)
	// 	{
	// 		ft_bzero(tmp->content, ft_strlen(tmp->content));
	// 		tmp->content = ft_strjoin("SHLVL=", mini_putnbr(s->var.shlvl));
	// 	}
	// 	tmp = tmp->next;
	// }
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_mini	s;
	char	*line;
	int		status = 1;
	int		i = 0;
	int		j = 0;
	int 	flag = 0;

	s.mass3d = (char ***)ft_calloc(sizeof(char **), 100);
	init_list(&s, env);
	init_list_x(&s, env);
	ft_shlvl(&s, env);
	while (status)
	{
		ft_init(&s);
		ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDOUT);
		status = get_next_line(&line);
		s.div_pipe = ft_split(line, '|');
		i = 0;
		while (s.div_pipe[i])
		{
			flag = 1; 
			// printf("p|%s|\n", s.div_pipe[i]);
			s.mass3d[i] = ft_split(s.div_pipe[i], ' ');
			s.pipe.count_commands++;
			i++;
			// printf("i = |%d|\n", i);
		}
		free(line);
		if (flag != 0)
		{	
			sort_ft(&s, env);
			ft_memdel_2d((void**)s.div_pipe);
		}
		i = 0;
	}
	return (0);
}






































