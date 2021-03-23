/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:11 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/23 16:49:11 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_arr_strswap(char ***str_array, int i, int j)
{
	char	*tmp;
	char	**array;

	array = *str_array;
	tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

void	ft_arr_intswap(int **int_array, int i, int j)
{
	int	tmp;
	int	*array;

	array = *int_array;
	tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

void	free_command(t_mini *s)
{
	int i;

	i = -1;
	while (++i < s->pipe.count_commands)
	{
		ft_memdel_2d((void **)s->mass3d[i]);
	}
	ft_memdel_2d((void **)s->pipes);
	ft_memdel_1d((void *)s->array_fdin);
	ft_memdel_1d((void *)s->array_fdout);
	free(s->mass3d);
	s->mass3d = NULL;
}

int		detect_out_redirect_type(const char *str, int position)
{
	int	out;

	out = 0;
	if (str[position] == '>' && str[position + 1] == '>')
		out = 2;
	else if (str[position + 1] != '>')
		out = 1;
	return (out);
}
