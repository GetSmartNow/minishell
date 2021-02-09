/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:04:38 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/08 19:57:59 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (++len);
}

char		*ft_itoa(int n)
{
	int		flag;
	int		len;
	char	*c;

	len = 0;
	flag = 0;
	len = ft_count(n);
	if (n == -2147483648)
		return (c = ft_strdup("-2147483648"));
	c = (char *)malloc(sizeof(char) * len + 1);
	if (c == NULL)
		return (NULL);
	c[len] = '\0';
	if (n < 0)
	{
		flag = 1;
		n = -n;
		c[0] = '-';
	}
	while (--len >= (flag ? 1 : 0))
	{
		c[len] = n % 10 + '0';
		n = n / 10;
	}
	return (c);
}
