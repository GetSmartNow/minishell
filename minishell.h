/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:17:23 by ctycho            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/02/23 18:53:01 by ctycho           ###   ########.fr       */
=======
/*   Updated: 2021/02/23 01:22:39 by ctycho           ###   ########.fr       */
>>>>>>> 733b0e798a04979ff0dd967cbbc117ee9ad2bf59
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/include/libft.h"
#include "get_next_line/get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

typedef struct		s_flag
{
	int				oldpwd;
}					t_flag;

typedef struct		s_pipe
{
	int				count_pipe;
	int				count_commands;
	// char			**div_pipe;
}					t_pipe;

typedef struct		s_mass
{
	void			*content;
	struct s_mass	*next;
	struct s_mass	*prev;
}					t_mass;

typedef struct		s_env
{
	char			*bin;
	int				shlvl;
}					t_env;

typedef struct		s_mini
{
	t_flag			flag;
	t_pipe			pipe;
	t_mass			*head;
	t_mass			*head_x;
	t_env			var;
	char			**arg;
	char			***mass3d;
	char			**env;
	char			**div_pipe;
	char			*tmp;
}					t_mini;

int					mini_bin(t_mini *s);
void				mini_cd(t_mini *s);
void				mini_pwd(t_mini	*s);
void				mini_echo(char **s);
void				mini_exit(char **s);
void				mini_env(t_mini *s);
void				mini_export(t_mini *s);
void				mini_unset(t_mini *s);
int					mini_pipes(t_mini *s);

int					length_to_equal(t_mini *s, char *line);
char				*put_quotes(char *s1);
void				ft_error(char *error, int flag);

t_mass				*my_lstnew(void *content);
void				my_lstadd_back(t_mass **lst, t_mass *new);
void				my_lstdelone(t_mass *lst, void (*del)(void *));
t_mass			*deletelem(t_mass *lst);
void			ft_list_sort(t_mass **lst, int cmp);

#endif