/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:49:30 by ctycho            #+#    #+#             */
/*   Updated: 2020/11/11 17:42:16 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **s, int v)
{
	int i;

	i = v;
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

static int	ft_count(char const *s, char c)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			n++;
		}
		s++;
	}
	return (n);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		words;
	int		start;
	char	**arr;

	i = 0;
	j = -1;
	if (s == 0)
		return (0);
	words = ft_count(s, c);
	if (!(arr = malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (++j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (!(arr[j] = ft_substr(s, start, i - start)))
			ft_free(arr, j);
		i++;
	}
	arr[j] = NULL;
	return (arr);
}
