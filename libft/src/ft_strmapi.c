/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:51:24 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/04 17:48:37 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*c;

	i = 0;
	if (s == 0)
		return (0);
	c = malloc(ft_strlen(s) + 1);
	if (c == NULL)
		return (NULL);
	while (s[i])
	{
		c[i] = (*f)(i, s[i]);
		i++;
	}
	c[i] = '\0';
	return (c);
}
