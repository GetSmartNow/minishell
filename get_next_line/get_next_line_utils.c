/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:55:50 by ctycho            #+#    #+#             */
/*   Updated: 2021/01/28 14:55:14 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*strdup_till_null(char *s)
{
	int			i;
	char		*arr;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (!(arr = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

size_t			ft_strlen_1(const char *s)
{
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char			*ft_join_str(char *s1, char *s2)
{
	size_t		i;
	size_t		m;
	char		*arr;

	i = ft_strlen_1(s1);
	m = ft_strlen_1(s2);
	if (!(arr = (char *)malloc(sizeof(char) * (i + m + 1))))
		return (NULL);
	i = 0;
	m = 0;
	if (s1)
		while (s1[i])
		{
			arr[i] = s1[i];
			i++;
		}
	while (s2[m])
		arr[i++] = s2[m++];
	if (s1)
		free(s1);
	arr[i] = '\0';
	return (arr);
}
