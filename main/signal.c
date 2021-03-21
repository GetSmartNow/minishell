/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 07:41:42 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/21 20:25:52 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				exit_code(t_mini *s)
{
	char			*nbr;

	nbr = ft_itoa(g_sig.exit_status);
	write(1, "bash: ", 6);
	write(1, nbr, ft_strlen(nbr));
	write(1, ": command not found\n", 20);
	ft_memdel_1d(nbr);
	g_sig.exit_status = 127;
}

void				sig_int(int signum)
{
	wait(NULL);
	if (g_sig.pid == 0)
	{
		write(1, "\b\b  \b\b\n", 7);
		ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
		g_sig.exit_status = 1;
		sigint = 1;
	}
	else
	{
		write(1, "\n", 1);
		g_sig.exit_status = 130;
	}
}

void				sig_quit(int code)
{
	char			*nbr;
	
	wait(NULL);
	if (g_sig.pid == 0)
	{
		write(1, "\b\b  \b\b", 7);
		g_sig.exit_status = 127;
	}
	else
	{
		write(1, "Quit: 3", 7);
		write(1, "\n", 1);
		g_sig.exit_status = 131;
	}
}

void				init_signal(void)
{
	g_sig.pid = 0;
	sigint = 0;
	sigd = 0;
}