/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:43:03 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/16 12:43:15 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				mini_echo(char **s)
{
	int				i;

	i = 0;
	if (s[1] == NULL)
		write(1, "\n", 1);
	else if (ft_strcmp(s[1], "-n") == 0)
	{
		i = 1;
		while (s[++i])
		{
			write(1, s[i], ft_strlen(s[i]));
			s[i + 1] != NULL ? write(1, " ", 1) : 0;
		}
	}
	else
	{
		while (s[++i])
		{
			write(1, s[i], ft_strlen(s[i]));
			s[i + 1] != NULL ? write(1, " ", 1) : 0;
		}
		write(1, "\n", 1);
	}
}