/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:46 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/23 16:57:53 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	define_fd_in(t_mini *s, char *line)
{
	int		position;
	char	*file_name;
	int		iter;
	int		fd;
	int		len;

	iter = 0;
	s->fdin = -1;
	file_name = NULL;
	while (line[iter])
	{
		position = find_symbol(line + iter, '<', s);
		if (position >= 0)
		{
			len = 0;
			ft_memdel_1d((void *)file_name);
			file_name = find_file_name(line + iter, position, &len);
			if (NULL == file_name)
				paste_error("malloc error\n", s);
			if (s->fdin != -1)
				close(s->fdin);
			fd = open(file_name, O_RDONLY);
			if (fd < 0)
				paste_error("input file error\n", s);
			else
				s->fdin = fd;
			iter += position + 1;
		}
		else
		{
			if (s->fdin == -1)
				s->fdin = STDIN;
			break ;
		}
	}
	ft_memdel_1d((void *)file_name);
}

void	define_fd_out(t_mini *s, char *line)
{
	int		position;
	char	*file_name;
	int		iter;
	int		len;

	iter = 0;
	file_name = NULL;
	s->fdout = -1;
	while (line[iter])
	{
		position = find_symbol(line + iter, '>', s);
		if (position >= 0)
		{
			len = 0;
			ft_memdel_1d((void *)file_name);
			file_name = find_file_name(line + iter, position, &len);
			if (NULL == file_name)
				paste_error("malloc error\n", s);
			iter += position + ft_fill_fd(s, line + iter, file_name, position);
		}
		else
		{
			if (s->fdout == -1)
				s->fdout = STDOUT;
			break ;
		}
	}
	ft_memdel_1d((void *)file_name);
}

int		ft_fill_fd(t_mini *s, char *line, char *file_name, int position)
{
	int fd_type;

	fd_type = detect_out_redirect_type(line, position);
	if (s->fdout != -1)
		close(s->fdout);
	if (fd_type == 2)
		s->fdout = open(file_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (fd_type == 1)
		s->fdout = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (s->fdout < 0)
		paste_error("output file error\n", s);
	return (fd_type);
}
