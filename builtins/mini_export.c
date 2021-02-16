/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:46:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/16 12:46:41 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				mini_export(t_mini *s)
{
	int				i;

	i = 0;
	if (!(s->arg[1]))
		while (s->env[i] != NULL)
		{
			write(1, "declare -x ", 11);
			write(1, s->env[i], ft_strlen(s->env[i]));
			write(1, "\n", 1);
			i++;
		}
}