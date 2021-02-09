/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:34:27 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/07 12:57:34 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	count;
	char	*str;

	i = 0;
	count = 0;
	str = (char *)src;
	if (len == 0)
		return (ft_strlen(str));
	if (dest == 0 && src == 0)
		return (0);
	count = len - 1;
	while (src[i] && i < count)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
