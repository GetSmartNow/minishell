/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:44:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/21 18:56:53 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			check_number(char *s)
{
	int				i = 0;
	int				res;
	int				count;

	count = 0;
	res = 0;
	while (s[i] && count < 20)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res = (res * 10) + (s[i] - 48);
			count++;
		}
		else
			return (255);
		i++;
	}
	if (count > 19)
		res = 255;
	else if (res > 255)
		res = (res % 255) - 1;
	return (res);
}

int				mini_exit(t_mini *s, char *exec, char *arg)
{
	int				res;

	write(1, exec, ft_strlen(exec));
	write(1, "\n", 1);
	if (ft_arrlen(s->mass3d[0]) > 2)
	{
		printf("%d\n", (int)ft_strlen_1(s->mass3d[0][2]));
		write(STDERR, "bash: exit: too many arguments\n", 31);
	}
	else if (arg)
	{
		s->exit = 1;
		res = check_number(arg);
		g_sig.exit_status = res;
		if (res == 255)
		{
			write(STDERR, "bash: exit: ", 12);
			write(STDERR, arg, ft_strlen(arg));
			write(STDERR, ": numeric argument required\n", 28);
		}
	}
	return (res);
}