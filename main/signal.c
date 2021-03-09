/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 07:41:42 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/09 11:01:04 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				sig_int(int signum)
{
	// printf("\npid: %d\n", g_sig.pid);
	printf("sig: %d\n", signum);
	if (g_sig.pid != 0)
	{
		write(1, "\n", 1);
		g_sig.exit_status = 130;
	}
	else
	{
		write(1, "\b\b  \b\b\n", 7);
		ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
		g_sig.exit_status = 1;
	}
}

void				sig_quit(int code)
{
	char			*nbr;
	
	if (g_sig.pid != 0)
	{
		write(1, "Quit: 3", 7);
		write(1, "\n", 1);
		g_sig.exit_status = 131;
	}
	else
	{
		write(1, "\b\b  \b\b", 7);
		g_sig.exit_status = 127;
	}
}

void				init_signal(void)
{
	g_sig.pid = 0;
}