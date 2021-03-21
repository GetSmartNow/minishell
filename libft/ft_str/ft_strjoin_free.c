/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:40:58 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/20 06:18:59 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin_free(char *s1, char *s2, char *free_str)
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
	ft_memdel_1d(free_str);
	arr[i] = '\0';
	return (arr);
}
