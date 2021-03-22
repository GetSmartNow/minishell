/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:52 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/22 14:16:53 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	paste_error(const char *str, t_mini *s)
{
	if (s->err_message == NULL)
		s->err_message = ft_strdup(str);
	s->err_status = 1;
}

void	print_error(t_mini *s)
{
	write(STDERR, "bash: ", 6);
	write(STDERR, s->err_message, ft_strlen(s->err_message));
}

void 	run_checks(char *str, t_mini *s)
{
	int position;
	int i;

	position = 0;
	i = 0;
	while (str[i] && position >=0)
	{
		position = find_symbol(str + i, '|', s);
		i += position + 1;
	}
	i = 0;
	position = 0;
	while (str[i] && position >=0)
	{
		position = find_symbol(str + i, '>', s);
		i += position + 1;
	}
	i = 0;
	position = 0;
	while (str[i] && position >=0)
	{
		position = find_symbol(str + i, '<', s);
		i += position + 1;
	}
}