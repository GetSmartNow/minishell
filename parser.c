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
	return ("");
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

static char	*ft_strnjoin_char(char *s1, char c, int quantity)
{
	char	*result;
	size_t	len;
	int		i;

	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	len = ft_strlen_modif(s1) + quantity + 1;
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

static char	*ft_concat(char *str1, char *str2)
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

static char	*extract_key(char *str, int pos)
{
	char	*res;

	res = NULL;
	//while (str[pos] && ft_isdigit((int)str[pos]))
	//	pos++;
	if (ft_isdigit(str[pos]))
		return (NULL);
	while (str[pos] && ft_isalnum((int)str[pos]))
	{
		res = ft_strnjoin_char(res, str[pos], 1);
		pos++;
	}
	return (res);
}

char	*extract_from_quotes(char *str, int pos)
{
	int		extract_start;

	extract_start = pos + 1;
	while (str[++pos])
	{
		if (str[pos] == '\'' && str[pos - 1] != '\\')
			return (ft_substr(str, extract_start, pos - extract_start));
	}
	return (NULL);
}

static int	is_shielded(char c)
{
	char	*shielded_list;
	int		i;

	shielded_list = "\\\"\'$;"; //maybe need add some extra
	i = 0;
	while (shielded_list[i])
	{
		if (shielded_list[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*make_substitute(char *command, t_mass **head)
{
	int		i;
	char	*res;
	char	*tmp;
	char	*key;
	int		count_shield;
	int		flag;

	tmp = NULL;
	res = NULL;
	i = 0;
	count_shield = 0;
	flag = 0;
	while (command[i])
	{
		if (command[i] == ' ')
			flag = 1;
		if (command[i] == '\\')
		{
			while (command[i] == '\\')
			{
				i++;
				count_shield++;
			}
			if (count_shield >= 2)
			{
				res = ft_strnjoin_char(res, '\\', count_shield / 2);
			}
			if (is_shielded(command[i]) && count_shield % 2 == 1)
			{
				res = ft_strnjoin_char(res, command[i], 1);
				i++;
				count_shield = 0;
			}
		}
		else if (command[i] == '\"')
		{
			i++;
		}
		else if (command[i] == '\'')
		{
			tmp = extract_from_quotes(command, i);
			if (tmp)
			{
				res = ft_concat(res, tmp);
				i += (ft_strlen_modif(tmp) + 2); //сомневаюсь насчет 2
			}
			else
			{
				tmp = ft_substr(command, i, ft_strlen_modif(command) - i);
				res = ft_concat(res, tmp);
				i += ft_strlen_modif(tmp);
			}
		}
		else if (command[i] == '$')
		{
			key = extract_key(command, ++i);
			printf("KEY: |%s|\n", key);
			if (NULL != key)
			{
				tmp = find_value_in_export(key, head);
				printf("TMP: |%s|\n", tmp);
				i += ft_strlen_modif(key);
				if (NULL != tmp && ft_strcmp(tmp, ""))
					res = ft_concat(res, tmp);
				else
					res = ft_strnjoin_char(res, '\0', 1);
			}
			else
			{
				i++; //no such key, just symbol, or mistake?
			}
		}
		else
		{
			if (!flag)
			{
				res = ft_strnjoin_char(res, ft_toupper(command[i]), 1);
				i++;
			}
			else
			{
				res = ft_strnjoin_char(res, command[i], 1);
				i++;
			}
		}
	}
	printf("RES: |%s|\n", res);
	return (res);
}