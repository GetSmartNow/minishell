/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:39:04 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/23 21:39:25 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	little_check(int shield_count, int *state, int *flag)
{
	if (shield_count % 2 == 1)
		(*flag) = 1;
	if ((*flag) == 0)
		(*state) = 0;
}

void	little_init(int *state, int *count, int *flag, int *shield_count)
{
	(*flag) = 0;
	(*state) = 0;
	(*count) = 0;
	(*shield_count) = 0;
}
