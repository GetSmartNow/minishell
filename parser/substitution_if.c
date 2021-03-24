/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:56 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/24 00:01:26 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_shield(const char *command, int *count_shield, int *i, char **res)
{
	(*i) += skip_symbol(command + (*i), count_shield, '\\');
	if ((*count_shield) >= 2)
	{
		(*res) = ft_strnjoin_char((*res), '\\', (*count_shield) / 2);
	}
	if (is_shielded(command[(*i)]) && (*count_shield) % 2 == 1)
	{
		(*res) = ft_strnjoin_char((*res), command[(*i)], 1);
		(*i)++;
	}
	(*count_shield) = 0;
	return (-1);
}

int	if_single_quote(char *command, t_mini *s, int *i, char **res)
{
	char *tmp;

	tmp = extract_from_quotes(command, (*i));
	if (tmp)
	{
		(*res) = ft_concat((*res), tmp);
		(*i) += (ft_strlen_modif(tmp) + 2);
	}
	else
		paste_error("quote is not closed\n", s);
	return (-1);
}

int	if_dollar(char *command, t_mass **head, int *counter, char **res)
{
	int	i;

	i = 0;
	if (!ft_strncmp(command, "$?", 2))
		i = errno_handler(command, counter, res);
	else
		i = replace(command, head, res);
	*counter = -2;
	return (i + 1);
}

int	if_double_quote(int *i, int *flag1)
{
	(*i)++;
	(*flag1)++;
	return (-1);
}
