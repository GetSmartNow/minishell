/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:37:14 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/04 17:33:10 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	char		*dmove;
	const char	*c;
	const char	*cmove;

	d = (char *)dst;
	c = (const char *)src;
	if (d < c)
	{
		while (len--)
			*d++ = *c++;
	}
	else if (d > c)
	{
		cmove = c + (len - 1);
		dmove = d + (len - 1);
		while (len--)
			*dmove-- = *cmove--;
	}
	if (dst == NULL && src == NULL && len == 0)
		return (NULL);
	return (dst);
}
