/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:55:26 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/21 21:06:26 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*find_null(char *remainder)
{
	size_t			stop;
	size_t			i;
	char			*s;

	stop = 0;
	i = 0;
	i = ft_strlen_1(remainder);
	while (remainder[stop] && remainder[stop] != '\n')
		stop++;
	if (!remainder[stop])
	{
		free(remainder);
		return (0);
	}
	if (!(s = (char *)malloc(sizeof(char) * (i - stop + 1))))
		return (NULL);
	stop++;
	i = 0;
	while (remainder[stop])
		s[i++] = remainder[stop++];
	s[i] = '\0';
	free(remainder);
	return (s);
}

int					check_end(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

int					caught_signal(char *remainder, int byte_was_read)
{
	if (byte_was_read == 0)
	{
		write(1, "  \b\b", 4);
		if (ft_strlen_1(remainder) != 0)
		{
			sigd = 1;
			byte_was_read = 1;
		}
		else
			write(1, "exit\n", 5);
	}
	return (byte_was_read);
}

int					get_next_line(char **line)
{
	char			*buf;
	int				byte_was_read;
	static char		*remainder;

	byte_was_read = 1;
	if (!(buf = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	while (!check_end(remainder) && byte_was_read != 0)
	{
		if ((byte_was_read = read(0, buf, 1)) < 0)
		{
			free(buf);
			return (-1);
		}
		buf[byte_was_read] = '\0';
		remainder = ft_join_str(remainder, buf);
		byte_was_read = caught_signal(remainder, byte_was_read);
		if (byte_was_read == 0)
			return (0);
	}
	free(buf);
	*line = strdup_till_null(remainder);
	remainder = find_null(remainder);
	return (byte_was_read ? 1 : 0);
}
