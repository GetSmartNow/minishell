/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:17:40 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/22 21:07:28 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		len_cur_word(char const *s, char sep)
{
	int	length;
	int	i;
	int	flag;
	int	shield_count;

	i = 0;
	length = 0;
	shield_count = 0;
	flag = 0;
	while (s[i])
	{
		i += skip_symbol(s + i, &shield_count, '\\');
		if (s[i] && is_quote(s[i]))
			define_flag2(shield_count, &flag);
		else if (s[i] && s[i] == sep)
		{
			if (shield_count % 2 == 1)
				flag = 1;
			if (flag == 0)
				return (i);
		}
		shield_count = 0;
		i++;
	}
	return (i);
}

static size_t	count_words(char const *s, char sep)
{
	int		state;
	int		count;
	int		i;
	int		flag;
	int		shield_count;

	flag = 0;
	i = 0;
	state = 0;
	count = 0;
	shield_count = 0;
	while (s[i])
	{
		i += skip_symbol(s + i, &shield_count, '\\');
		if (s[i] && is_quote(s[i]))
			define_flag2(shield_count, &flag);
		if (s[i] && s[i] != sep && state == 0)
		{
			count++;
			state = 1;
		}
		else if (s[i] == sep)
		{
			if (shield_count % 2 == 1)
				flag = 1;
			if (flag == 0)
				state = 0;
		}
		shield_count = 0;
		i++;
	}
	return (count);
}

static void		*my_free(char **array, size_t i)
{
	while (i-- >= 0)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
	return (NULL);
}

static size_t	create_str(const char *s, char c, char **arr, size_t *iter)
{
	int	len_word;

	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			len_word = len_cur_word(s, c);
			arr[*iter] = ft_substr(s, 0, len_word);
			s += len_word;
			if (NULL == arr[*iter])
				return (1);
			*iter += 1;
		}
	}
	return (0);
}

char			**ft_split_new(char const *s, char c)
{
	char	**arr;
	size_t	iter;
	int		num_words;

	if (!s)
		return (NULL);
	iter = 0;
	num_words = count_words(s, c);
	arr = (char **)malloc((num_words + 1) * sizeof(char *));
	if (NULL == arr)
		return (NULL);
	if (create_str(s, c, arr, &iter))
		return (my_free(arr, iter));
	arr[iter] = NULL;
	return (arr);
}
