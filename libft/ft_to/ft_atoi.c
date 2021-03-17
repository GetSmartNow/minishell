/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:18:02 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/24 15:49:39 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
