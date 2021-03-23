/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:32:58 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/23 21:40:09 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void			empty_olpwd(t_mini *s)
{
	t_mass			*tmp;

	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			ft_memdel_1d(tmp->content);
			tmp->content = ft_strdup("OLDPWD=");
		}
		tmp = tmp->next;
	}
	tmp = s->head_x;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			ft_memdel_1d(tmp->content);
			tmp->content = put_quotes("OLDPWD=");
		}
		tmp = tmp->next;
	}
}

static int			mini_cd_minus_2(t_mini *s, char *arg, int res)
{
	if (s->var.oldpwd != NULL)
	{
		write(STDOUT, s->var.oldpwd, ft_strlen(s->var.oldpwd));
		write(STDOUT, "\n", 1);
		res = chdir(s->var.oldpwd);
	}
	else
		res = chdir(arg);
	ft_memdel_1d(s->var.oldpwd);
	return (res);
}

static void			mini_cd_minus_1(t_mini *s)
{
	t_mass			*tmp;
	int				flag;

	flag = 0;
	tmp = s->head;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			flag = 1;
			if (ft_strlen(tmp->content) == ft_strlen("OLDPWD="))
				write(1, "bash: cd: OLDPWD not set\n", 25);
			else
				s->var.oldpwd = ft_strdup(tmp->content + 7);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		write(1, "bash: cd: OLDPWD not set\n", 25);
}

static int			mini_cd_minus(t_mini *s, char *arg)
{
	int				res;
	int				len;

	res = 1;
	len = ft_strlen(arg);
	if (arg[0] == '-' && len >= 1)
	{
		if ((len == 2 && arg[1] == '-') || len == 1)
			mini_cd_minus_1(s);
		else
		{
			res = 0;
			write(1, "bash: cd: ", 10);
			write(1, arg, 2);
			write(1, ": invalid option\n", 17);
			write(1, "cd: usage: cd [-L|-P] [dir]\n", 28);
		}
	}
	if (res == 1)
		res = mini_cd_minus_2(s, arg, res);
	return (res);
}

void				mini_cd(t_mini *s, char *arg)
{
	int				res;

	res = 0;
	if (arg == NULL)
	{
		get_home(s);
		return ;
	}
	res = mini_cd_minus(s, arg);
	if (res == -1 && s->mass3d[0][1][0] != '-')
	{
		write(1, "bash: cd: ", 10);
		write(1, arg, ft_strlen(arg));
		write(1, ": No such file or directory\n", 28);
		g_sig.exit_status = 1;
	}
	else
	{
		if (s->var.pwd == 0)
			mini_oldpwd(s);
		else
			empty_olpwd(s);
		mini_pwd_1(s);
	}
}
