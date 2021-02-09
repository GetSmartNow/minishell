/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:27:31 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/07 13:57:22 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t i;
	size_t j;
	size_t n;

	i = 0;
	j = 0;
	i = ft_strlen(dest);
	n = ft_strlen(src);
	if (len <= i)
		n = n + len;
	else
		n = n + i;
	while (src[j] && i + 1 < len)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (n);
}
