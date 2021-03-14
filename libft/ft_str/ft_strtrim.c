/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:48:56 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/08 19:52:18 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t i;
	size_t n;
	size_t m;

	i = 0;
	m = 0;
	if (!s1)
		return (NULL);
	n = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (i == n)
		return (ft_substr("", 0, 1));
	while (ft_strrchr(set, s1[n - m - 1]))
		m++;
	return (ft_substr(s1, i, n - i - m));
}
