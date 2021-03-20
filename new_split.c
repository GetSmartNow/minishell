// #include "libft/include/libft.h"
// #include <stdio.h>
#include "minishell.h"

static int		len_cur_word(char const *s, char sep)
{
	int		length;
	int		flag;
	int		shield_count;

	flag = 0;
	length = 0;
	shield_count = 0;
	while (*s)
	{
		while (*s && *s == '\\')
		{
			shield_count++;
			length++;
			s++;
		}
		if (*s && *s != sep)
		{
			//if (shield_count % 2 == 1)
			//{
			//	if (*s == '\'' || *s == '\"')
			//	{
			//		s++;
			//		length++;
			//		shield_count = 0;
			//	}
			//}
			if (shield_count % 2 == 0)
			{
				if ((*s == '\'' || *s == '\"') && flag == 1)
				{
					flag = 0;
					shield_count = 0;
				}
				else if ((*s == '\'' || *s == '\"') && flag == 0)
				{
					flag = 1;
					shield_count = 0;
				}
			}
			else
				shield_count = 0;
			s++;
			length++;
			//if ((*s == '\'' || *s == '\"') && shield_count % 2 == 1)
			//{
			//	flag = 0;
			//	shield_count = 0;
			//}
			//else if ((*s == '\'' || *s == '\"') && shield_count % 2 == 0)
			//{
			//	flag = 1;
			//	shield_count = 0;
			//}
			//s++;
			//length++;
			//if (*s == sep && (flag == 1 || shield_count % 2 == 1))
			//{
			//	printf("SH COUNT: |%d|\n", shield_count);
			//	s++;
			//	length++;
			//}
		}
		else if (*s == sep && shield_count % 2 == 1)
		{
			s++;
			length++;
			shield_count = 0;
		}
		else if (*s == sep && flag == 0)
			return (length);
	}
	//printf("LENGTH: |%d|\n", length);
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
		if (s[i] == '\\')
		{
			i++;
			shield_count++;
		}
		else
		{
			if ((s[i] == '\'' || s[i] == '\"') && flag == 1 && (shield_count % 2 != 1))
			{
				flag = 0;
				shield_count = 0;
			}
			else if ((s[i] == '\'' || s[i] == '\"') && flag == 0 && (shield_count % 2 != 1))
			{
				flag = 1;
				shield_count = 0;
			}
			if (s[i] == sep && state == 1 && shield_count % 2 != 1)
			{
				state = 0;
				shield_count = 0;
			}
			if (s[i] != sep && state == 0 && flag == 0)
			{
				count++;
				state = 1;
			}
			i++;
		}
	}
	//printf("COUNT: |%d|\n", count);
	return (count);
}

static void		*my_free(char **array, size_t i)
{
	while (i-- >= 0)
		free(array[i]);
	free(array);
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
			*iter += 1;
			//arr[*iter] = (char *)malloc(len_word + 1);
			//if (NULL == arr[*iter])
			//	return (1);
			//i = 0;
			//while (i < len_word && *s)
			//	arr[*iter][i++] = *s++;
			//arr[(*iter)++][i] = '\0';
			//printf("FROM SPLIT: |%s|\n", arr[*iter - 1]);
		}
	}
	return (0);
}

char			**ft_split_new(char const *s, char c)
{
	char	**arr;
	size_t	iter;
	int		length;

	if (!s)
		return (NULL);
	iter = 0;
	length = count_words(s, c);
	arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (NULL == arr)
		return (NULL);
	if (create_str(s, c, arr, &iter))
		return (my_free(arr, iter));
	arr[iter] = NULL;
	return (arr);
}

// int main(int argc, char *argv[])
// {
// 	char *line = "ls | cat -e";
// 	printf("line: %s\n", line);
// 	if (argc)
// 	{
// 		char **splited = ft_split_new(line, '|');
// 		while (*splited)
// 		{
// 			printf("%s\n", *splited);
// 			splited++;
// 		}
// 		printf("%s\n", *splited);
// 	}
// }