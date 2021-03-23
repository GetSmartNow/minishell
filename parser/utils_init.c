/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:43 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/23 16:54:32 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_before_replacement(int *i, char **res,
	int *count_shield, int *flag1)
{
	(*flag1) = 0;
	(*res) = NULL;
	(*i) = 0;
	(*count_shield) = 0;
}

void	init_err_info(t_mini *s)
{
	s->err_message = NULL;
	s->err_status = 0;
}

void	init_fs(int *iter, int *shield_count, int *position, int *flag)
{
	(*iter) = 0;
	(*shield_count) = 0;
	(*position) = -1;
	(*flag) = 0;
}
