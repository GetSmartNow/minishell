/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:17:40 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/21 15:27:27 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"

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
		while (s[i] == '\\')
		{
			i++;
			shield_count++;
			length++;
		}
		if (s[i] && (s[i] == '\'' || s[i] == '\"') && flag == 0)
		{
			if (shield_count % 2 == 0)
			{
				flag = 1;
			}
			shield_count = 0;
			length++;
		}
		else if (s[i] && (s[i] == '\'' || s[i] == '\"') && flag == 1)
		{
			if (shield_count % 2 == 0)
			{
				flag = 0;
			}
			shield_count = 0;
			length++;
		}
		else if (s[i] && s[i] != sep)
		{
			shield_count = 0;
			length++;
		}
		else if (s[i] && s[i] == sep)
		{
			if (shield_count % 2 == 1)
				flag = 1;
			if (flag == 1)
				length++;
			else
				return (length);
			shield_count = 0;
		}
		i++;
	}
	return (length);
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
		while (s[i] == '\\')
		{
			i++;
			shield_count++;
		}
		if (s[i] && (s[i] == '\'' || s[i] == '\"') && flag == 0)
		{
			if (shield_count % 2 == 0)
				flag = 1;
			// shield_count = 0;
		}
		else if (s[i] && (s[i] == '\'' || s[i] == '\"') && flag == 1)
		{
			if (shield_count % 2 == 0)
				flag = 0;
			// shield_count = 0;
		}
		if (s[i] && s[i] != sep && state == 0)
		{
			count++;
			state = 1;
			// shield_count = 0;
		}
		else if (s[i] == sep)
		{
			if (shield_count % 2 == 1)
			{
				// shield_count = 0;
				flag = 1;
			}
			else
				// shield_count = 0;
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
	int	i;

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
			//printf("FROM SPLIT: |%s|\n", arr[*iter - 1]);
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
	//printf("COUNT: %d\n", num_words);
	arr = (char **)malloc((num_words + 1) * sizeof(char *));
	if (NULL == arr)
		return (NULL);
	if (create_str(s, c, arr, &iter))
		return (my_free(arr, iter));
	arr[iter] = NULL;
	return (arr);
}

//int	main(void)
//{
//	char *line = NULL;
//	int i;
//	while ((i = get_next_line(&line)))
//	{
//		char **arr = ft_split_new(line, ' ');
//		free(line);
//		line = NULL;
//	}
//}