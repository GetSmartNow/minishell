/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:34 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/23 16:52:37 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcut(char *line, int start, int len)
{
	char	*res;
	int		iter;
	int		i;

	i = 0;
	iter = -1;
	res = ft_strdup("");
	while (++iter < start)
	{
		res = ft_strnjoin_char(res, line[i], 1);
		i++;
	}
	iter = -1;
	while (++iter < len)
		i++;
	while (line[i])
	{
		res = ft_strnjoin_char(res, line[i], 1);
		i++;
	}
	ft_memdel_1d((void *)line);
	return (res);
}

char	*extract_command(char *line, char redir, t_mini *s)
{
	int		len;
	char	*res;
	int		iter;
	int		position;
	char	*file_name;

	file_name = NULL;
	iter = 0;
	res = ft_strdup(line);
	if (NULL == res)
		paste_error("malloc error\n", s);
	position = 0;
	while (*res && position >= 0)
	{
		position = find_symbol(res, redir, s);
		if (position >= 0)
		{
			len = 0;
			ft_memdel_1d(file_name);
			file_name = find_file_name(res, position, &len);
			if (NULL == file_name)
				paste_error("malloc error\n", s);
			res = ft_strcut(res, iter + position, len);
		}
	}
	ft_memdel_1d((void *)file_name);
	ft_memdel_1d((void *)line);
	return (res);
}

char	*extract_file_name(char *line, char redir, t_mini *s)
{
	int		len;
	int		iter;
	int		position;
	char	*file_name;

	iter = 0;
	position = 0;
	file_name = NULL;
	while (line[iter] && position >= 0)
	{
		position = find_symbol(line + iter, redir, s);
		if (position >= 0)
		{
			len = 0;
			ft_memdel_1d(file_name);
			file_name = find_file_name(line + iter, position, &len);
			if (NULL == file_name)
				paste_error("malloc error\n", s);
			iter += position + 1;
		}
	}
	return (file_name);
}

char	*find_file_name(char *line, int position, int *len)
{
	int	counter;
	int	start;

	counter = 0;
	while (line[position] && !ft_isalnum(line[position]))
	{
		position++;
		*len += 1;
	}
	start = position;
	while (line[position] && (ft_isalnum(line[position]) ||
		line[position] == '.'))
	{
		counter++;
		position++;
		*len += 1;
	}
	while (line[position] && (ft_isspace(line[position])))
	{
		*len += 1;
		position++;
	}
	return (ft_substr(line, start, counter));
}
