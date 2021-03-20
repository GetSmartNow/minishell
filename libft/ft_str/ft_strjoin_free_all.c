/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_all.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:44:39 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/20 06:19:08 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin_free_all(char *s1, char *s2)
{
	size_t		i;
	size_t		m;
	char		*arr;

	i = ft_strlen_1(s1);
	m = ft_strlen_1(s2);
	if (!(arr = (char *)malloc(sizeof(char) * (i + m + 1))))
		return (NULL);
	i = -1;
	m = 0;
	while (s1[++i])
		arr[i] = s1[i];
	while (s2[m])
		arr[i++] = s2[m++];
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	arr[i] = '\0';
	return (arr);
}
