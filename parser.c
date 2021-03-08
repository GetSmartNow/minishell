#include "minishell.h"

char	*find_value_in_export(char *key, t_mass **head)
{
	char	*value;
	t_mass	*node;
	char 	*tmp;
	size_t	key_len;

	key_len = ft_strlen(key);
	node = *head;
	tmp = node->content;
	while (node)
	{
		if (!ft_strncmp(key, tmp, key_len) && ((char *)(node->content))[key_len] == '=')
		{
			value = ft_substr(tmp, key_len + 1, (ft_strlen(tmp) - (key_len + 1)));
			return (value);
		}
		node = node->next;
		if (node != NULL)
			tmp = node->content;
	}
	//while (node && ft_strncmp(key, tmp, key_len))
	//{
	//	node = node->next;
	//	if (node != NULL)
	//		tmp = node->content;
	//}
	//if (node != NULL)
	//{
	//	value = ft_substr(tmp, key_len + 1, (ft_strlen(tmp) - (key_len + 1)));
	//	return (value);
	//}
//	printf("%s\n", value);
	return ("");
}

static char	*ft_strnjoin_char(char *s1, char c, int quantity)
{
	char	*result;
	size_t	len;
	int		i;

	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	len = ft_strlen(s1) + quantity + 1;
	result = (char *)malloc(len * sizeof(char));
	if (NULL == result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (quantity--)
		result[i++] = c;
	result[i] = '\0';
	free(s1);
	return (result);
}

static char	*extract_key(char *str, int pos)
{
	char	*res;

	res = NULL;
	while (str[pos] && ft_isalnum((int)str[pos]))
	{
		res = ft_strnjoin_char(res, str[pos], 1);
		pos++;
	}
	return (res);
}
static int	ft_strlen_modif(const char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static char	*ft_concatenate(char *str1, char *str2)
{
	int		len;
	int		i;
	int		j;
	char	*res;

	len = ft_strlen_modif(str1) + ft_strlen_modif(str2) + 1;
	res = (char *)malloc(len * sizeof(char));
	j = 0;
	i = 0;
	if (str1)
		while (str1[j])
			res[i++] = str1[j++];
	j = 0;
	if (str2)
		while (str2[j])
			res[i++] = str2[j++];
	res[i] = '\0';
	if (str1 != NULL)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2 != NULL)
	{
		free(str2);
		str2 = NULL;
	}
	return (res);
}



char	*make_substitute(char *sep_commands, t_mass **head)
{
	/*
	 * 1. Если открывающий символ ' то дальше все воспринимается, как
	 * написано. Только текст. Экранирования не работают в том числе. Сами
	 * кавычки не печатаются (затираются)
	 * 2. Если открывающий символ ", то дальше возможна подстановка переменных
	 * экранирование будет работать.
	 *
	 * */
	t_mass	*node;
	char	*key;
	int 	i;
	char	*res;
	char *tmp;

	i = 0;
	node = *head;
	res = NULL;
	key = NULL;
	tmp = NULL;
	while (sep_commands[i])
	{
		if (sep_commands[i] == '$')
		{
			key = extract_key(sep_commands, ++i);
			printf("key ------ %s\n", key);
			if (key != NULL)
			{
				tmp = find_value_in_export(key, head);
				printf("tmp ------ %s\n", tmp);
				i += ft_strlen(key);
				res = ft_concatenate(res, tmp);
			}
			else
			{
//				res = ft_strnjoin_char(res, sep_commands[i], 1);
//				i++;
				printf("Error: fucked up extracting key\n");
			}
		}
		else
		{
			res = ft_strnjoin_char(res, sep_commands[i], 1);
			i++;
		}
	}
	printf("res ------ %s\n", res);
	return (res);
}