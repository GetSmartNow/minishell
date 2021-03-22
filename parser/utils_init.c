/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:43 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/22 14:16:44 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_before_replacement(int *i, char **res, int *count_shield, int *flag1)
{
	(*flag1) = 0;
	(*res) = NULL;
	(*i) = 0;
	(*count_shield) = 0;
}

void init_err_info(t_mini *s)
{
	s->err_message = NULL;
	s->err_status = 0;
}