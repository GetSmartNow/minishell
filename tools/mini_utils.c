/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:13:20 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/24 18:46:30 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					length_to_equal(t_mini *s, char *line)
{
	int				i = 0;

	while (line[i] != '=' && line[i] != '\0')
		i++;
	return (i);
}

char				*put_quotes(char *s1)
{
	int		i = 0;
	int		j = 0;
	int		flag = 0;
	char	*s = NULL;

	s = (char *)malloc(sizeof(char) * ft_strlen(s1) + 3);
	while (s1[j])
	{
		s[i] = s1[j];
		if (s1[j] == '=')
		{
			s[++i] = '"';
			flag = 1;
		}
		if (s1[j + 1] == '\0' && flag == 1)
			s[++i] = '"';
		i++;
		j++;
	}
	s[i] = '\0';
	return(s);
}

char			*mini_putnbr(int n)
{
	int				size;
	char			*s;
	int				i = 0;

	size = ft_intlen(n);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (n <= 9)
	{
		s[i] = n + '0';
		i++;
	}
	else
	{
		mini_putnbr(n / 10);
		mini_putnbr(n % 10);
	}
	return (s);
}