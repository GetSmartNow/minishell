/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:43:03 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/24 00:11:14 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			mini_echo_2(char *s)
{
	int				i;

	i = 1;
	while (s[i])
	{
		if (s[i] == 'n' && s[0] == '-')
			i++;
		else
			return (-1);
	}
	return (0);
}

static void			mini_echo_1(t_mini *s, char **str, int i)
{
	i = 1;
	while (str[i])
	{
		if (mini_echo_2(str[i]) == 0)
			i++;
		else
		{
			write(s->fdout, str[i], ft_strlen(str[i]));
			str[i + 1] != NULL ? write(s->fdout, " ", 1) : 0;
			i++;
		}
	}
}

void				mini_echo(char **str, t_mini *s)
{
	int				i;

	i = 0;
	if (str[1] == NULL)
		write(s->fdout, "\n", 1);
	else if (str[1][0] == '-' && str[1][1] == 'n' && mini_echo_2(str[1]) == 0)
		mini_echo_1(s, str, i);
	else
	{
		while (str[++i])
		{
			write(s->fdout, str[i], ft_strlen(str[i]));
			str[i + 1] != NULL ? write(s->fdout, " ", 1) : 0;
		}
		write(s->fdout, "\n", 1);
	}
	g_sig.exit_status = 0;
}
