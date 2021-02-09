/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:18:02 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/11 17:23:39 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int		ft_atoi(const char *str)
{
	int flag;
	int res;
	int check;

	flag = 1;
	res = 0;
	check = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if ((*str == '-') || (*str == '+'))
		if (*str++ == '-')
			flag = -flag;
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str++ - 48);
		check++;
		if (check > 19)
		{
			if (flag < 1)
				return (0);
			else
				return (-1);
		}
	}
	return (res * flag);
}

int		main(void)
{
	printf("%d\n", atoi("00000000000000000009"));
	printf("%d\n", ft_atoi("00000000000000000009"));
	return (0);
}
