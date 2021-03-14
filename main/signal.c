/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 07:41:42 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/14 14:17:04 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_sig.exit_status = 0;
	g_sig.pid = 0;
	sigint = 0;
}