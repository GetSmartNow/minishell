/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:17:23 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/16 23:46:53 by ctycho           ###   ########.fr       */
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

typedef struct		s_mass
{
	void			*content;
	struct s_mass	*next;
	struct s_mass	*prev;
}					t_mass;

typedef struct		s_env
{
	char			*bin;
	int				flag;
}					t_env;

typedef struct		s_mini
{
	t_mass			*head;
	t_env			var;
	char			**arg;
	char			***mass3d;
	char			**env;
	char			**pipes;
	char			*tmp;
}					t_mini;

int					mini_bin(t_mini *s);
void				mini_cd(t_mini *s);
void				mini_pwd(t_mini	*s);
void				mini_echo(char **s);
void				mini_exit(char **s);
void				mini_env(t_mini *s);
void				mini_export(t_mini *s);

t_mass				*my_lstnew(void *content);
void				my_lstadd_back(t_mass **lst, t_mass *new);
void				my_lstdelone(t_mass *lst, void (*del)(void *));

#endif