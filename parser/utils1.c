/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:19 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/22 14:16:21 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int skip_symbol(const char *str, int *symbol_count, char symbol)
{
	int iter;

	iter = 0;
	while (str[iter] && str[iter] == symbol)
	{
		(*symbol_count)++;
		iter++;
	}
	return (iter);
}

int is_quote(char symbol)
{
	if (symbol == '\'' || symbol == '\"')
		return (1);
	return (0);
}

int	ft_arrlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	ft_isspace(char c)
{
	int	result;

	result = 0;
	if (c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r' || c == ' ')
		result = 1;
	return (result);
}

int	ft_strlen_modif(const char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}
