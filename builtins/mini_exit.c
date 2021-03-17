/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:44:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/17 15:05:13 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			check_number(char *s)
{
	int				i = 0;
	int				res;

	res = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			res = (res * 10) + (s[i] - 48);
		else
			return (255);
		i++;
	}
	return (res);
}

int				mini_exit(t_mini *s, char *exec, char *arg)
{
	int				res;

	s->exit = 1;
	write(1, exec, ft_strlen(exec));
	write(1, "\n", 1);
	if (arg)
	{
		res = check_number(arg);
		g_sig.exit_status = res;
		if (res == 255)
		{
			write(STDOUT, "bash: exit: ", 12);
			write(STDOUT, arg, ft_strlen(arg));
			write(STDOUT, ": numeric argument required\n", 28);
		}
	}
	return (res);
}