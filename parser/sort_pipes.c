/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 20:57:27 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/23 21:51:26 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		create_fd(t_mini *s)
{
	int iter_pipes;

	iter_pipes = 0;
	while ((s->pipes)[iter_pipes])
	{
		define_fd_out(s, (s->pipes)[iter_pipes]);
		(s->array_fdout)[iter_pipes] = s->fdout;
		define_fd_in(s, (s->pipes)[iter_pipes]);
		(s->array_fdin)[iter_pipes] = s->fdin;
		iter_pipes++;
	}
}

void		make_swap(t_mini *s, int i, int j)
{
	ft_arr_strswap(&(s->pipes), i, j);
	ft_arr_intswap(&(s->array_fdin), i, j);
	ft_arr_intswap(&(s->array_fdout), i, j);
}

static void	init_sort_pipe(t_mini *s, int *i, char **file_name1,
			char **file_name2)
{
	(*i) = -1;
	create_fd(s);
	(*file_name1) = NULL;
	(*file_name2) = NULL;
}

void		ft_sort_pipes(t_mini *s)
{
	int		arr_len;
	int		i;
	int		j;
	char	*file_name1;
	char	*file_name2;

	arr_len = ft_arrlen(s->pipes);
	init_sort_pipe(s, &i, &file_name1, &file_name2);
	while (++i < arr_len - 1)
	{
		ft_memdel_1d((void *)file_name1);
		file_name1 = extract_file_name((s->pipes)[i], '<', s);
		j = i;
		while (++j < arr_len)
		{
			ft_memdel_1d((void *)file_name2);
			file_name2 = extract_file_name((s->pipes)[j], '>', s);
			if (file_name1 && file_name2)
				if (!ft_strcmp(file_name1, file_name2))
					make_swap(s, i, j);
		}
	}
	ft_memdel_1d(file_name2);
	ft_memdel_1d(file_name1);
}
