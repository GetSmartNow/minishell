/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 20:57:27 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/21 15:17:09 by mvernius         ###   ########.fr       */
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

void	create_fd(t_mini *s)
{
	int iter_pipes;

	iter_pipes = 0;
	while ((s->pipes)[iter_pipes])
	{
		//ОПРЕДЕЛЯЕМ FD IN & OUT
		define_fd_out(s, (s->pipes)[iter_pipes]);
		(s->array_fdout)[iter_pipes] = s->fdout;
		//printf("%d\n", (s->array_fdout)[iter_pipes]);
		define_fd_in(s, (s->pipes)[iter_pipes]);
		(s->array_fdin)[iter_pipes] = s->fdin;
		iter_pipes++;
	}
}

void	ft_sort_pipes(t_mini *s)
{
	int		arr_len;
	int		i;
	int		j;
	char	*file_name1;
	char	*file_name2;

	arr_len = ft_arrlen(s->pipes);
	i = 0;
	create_fd(s);
	while (i < arr_len - 1)
	{
		j = i + 1;
		file_name1 = extract_file_name((s->pipes)[i], '<');
		while (j < arr_len)
		{
			file_name2 = extract_file_name((s->pipes)[j], '>');
			if (file_name1 && file_name2)
			{
				if (!ft_strcmp(file_name1, file_name2))
				{
					ft_arr_strswap(&(s->pipes), i, j);
					ft_arr_intswap(&(s->array_fdin), i, j);
					ft_arr_intswap(&(s->array_fdout), i, j);
				}
			}
			j++;
		}
		i++;
	}
}