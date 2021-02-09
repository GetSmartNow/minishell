/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:51:39 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/08 20:10:08 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*f;

	i = 0;
	d = (unsigned char *)dst;
	f = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (NULL);
	while (i < n)
	{
		d[i] = f[i];
		i++;
	}
	return (dst);
}
