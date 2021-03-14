/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:14:31 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/04 17:38:26 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *s2, size_t len)
{
	size_t n;

	if (*s2 == 0)
		return ((char *)big);
	n = ft_strlen(s2);
	while (*big && len-- >= n)
	{
		if (*big == *s2 && ft_memcmp(big, s2, n) == 0)
			return ((char *)big);
		big++;
	}
	return (0);
}
