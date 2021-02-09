/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:19:56 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/04 17:45:33 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*c;

	i = 0;
	j = 0;
	c = (char *)malloc(sizeof(char) * (len + 1));
	if (c == NULL)
		return (NULL);
	if (!s)
		return (0);
	while (s[i])
	{
		if (i >= start && i < (start + len))
		{
			c[j] = s[i];
			j++;
		}
		i++;
	}
	c[j] = 0;
	return (c);
}
