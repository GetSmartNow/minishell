/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:43:03 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/23 16:58:05 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void			mini_echo_1(t_mini *s, char **str, int i)
{
	i = 1;
	while (str[i])
	{
		if (ft_strcmp(str[i], "-n") == 0)
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
	else if (ft_strcmp(str[1], "-n") == 0)
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
