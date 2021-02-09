/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:05:32 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/08 20:05:17 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*f;

	d = (unsigned char *)dst;
	f = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (NULL);
	while (n--)
	{
		if (*f == (unsigned char)c)
		{
			*d++ = *f++;
			return (d);
		}
		*d++ = *f++;
	}
	return (0);
}
