#include "libft/include/libft.h"
#include <stdio.h>

static int		len_cur_word(char const *s, char c)
{
	int		length;
	int		flag;

	flag = 0;
	length = 0;
	while (*s && (*s != c || *(s - 1) == '\\'))
	{
		if ((*s == '\'' || *s == '\"') && flag == 0)
			flag = 1;
		else if ((*s == '\'' || *s == '\"') && flag == 1)
			flag = 0;
		length++;
		s++;
		if (*s == c && flag)
		{
			s++;
			length++;
		}
	}
	return (length);
}

static size_t	count_words(char const *s, char c)
{
	int		state;
	size_t	count;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	state = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && flag == 1)
			flag = 0;
		else if ((s[i] == '\'' || s[i] == '\"') && flag == 0)
			flag = 1;
		if (s[i] == c && state == 1 && (i > 0 && s[i - 1] != '\\'))
			state = 0;
		if (s[i] != c && state == 0 && flag != 1)
		{
			count++;
			state = 1;
		}
		i++;
	}
	printf("count - %d\n", (int)count);
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
			arr[*iter] = (char *)malloc(len_word + 1);
			if (NULL == arr[*iter])
				return (1);
			i = 0;
			while (i < len_word && *s)
				arr[*iter][i++] = *s++;
			arr[(*iter)++][i] = '\0';
		}
	}
	return (0);
}

char			**ft_split_new(char const *s, char c)
{
	char	**arr;
	size_t	iter;

	if (!s)
		return (NULL);
	iter = 0;
	arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (NULL == arr)
		return (NULL);
	if (create_str(s, c, arr, &iter))
		return (my_free(arr, iter));
	arr[iter] = NULL;
	return (arr);
}

//int main(int argc, char *argv[])
//{
//	if (argc)
//	{
//		char **splited = ft_split_new(argv[1], ';');
//		while (*splited)
//		{
//			printf("%s\n", *splited);
//			splited++;
//		}
//		printf("%s\n", *splited);
//	}
//}