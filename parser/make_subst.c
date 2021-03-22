/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_subst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:17:17 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/22 21:06:47 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_substitute(char *command, t_mass **head, int counter, t_mini *s)
{
	int		i;
	char	*res;
	int		count_shield;
	int		flag1;

	init_before_replacement(&i, &res, &count_shield, &flag1);
	while (command[i] && s->err_status == 0)
	{
		if (command[i] == '\\')
			counter = if_shield(command, &count_shield, &i, &res);
		else if (command[i] == '\"')
			counter = if_double_quote(&i, &flag1);
		else if (command[i] == '\'')
			counter = if_single_quote(command, s, &i, &res);
		else if (command[i] == '$')
			i += if_dollar(command + i, head, &counter, &res);
		else
			add_simple_char(command[i], &i, &res, counter);
	}
	if (flag1 % 2 == 1)
		paste_error("quote is not closed\n", s);
	if (counter != -2 && res == NULL)
		paste_error("malloc error\n", s);
	return (res);
}
