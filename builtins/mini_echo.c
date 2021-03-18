/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:43:03 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/18 17:17:20 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				mini_echo(char **str)
{
	int				i;

	i = 0;
	if (str[1] == NULL)
		write(1, "\n", 1);
	else if (ft_strcmp(str[1], "-n") == 0)
	{
		i = 1;
		while (str[i])
		{
			if (ft_strcmp(str[i], "-n") == 0)
				i++;
			else
			{
				write(1, str[i], ft_strlen(str[i]));
				str[i + 1] != NULL ? write(1, " ", 1) : 0;
				i++;
			}
		}
	}
	else
	{
		while (str[++i])
		{
			write(1, str[i], ft_strlen(str[i]));
			str[i + 1] != NULL ? write(1, " ", 1) : 0;
		}
		write(1, "\n", 1);
	}
}