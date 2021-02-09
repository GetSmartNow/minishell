/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:09:17 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/04 17:46:19 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*c;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	c = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (c == NULL)
		return (NULL);
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		c[i] = s2[j];
		i++;
		j++;
	}
	c[i] = 0;
	return (c);
}
