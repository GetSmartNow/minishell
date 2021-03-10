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

	shielded_list = "\\\"\'$"; //maybe need add some extra
	i = 0;
	while (shielded_list[i])
	{
		if (shielded_list[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*make_substitute(char *sep_commands, t_mass **head)
{
	int		i;
	char	*res;
	char	*tmp;
	char	*key;

	tmp = NULL;
	res = NULL;
	i = 0;
	while (sep_commands[i + 1])
	{
		if (sep_commands[i] == '\\')
		{
			if (is_shielded(sep_commands[i + 1]))
			{
				res = ft_strnjoin_char(res, sep_commands[i + 1], 1);
				i += 2;
			}
			else
			{
				res = ft_strnjoin_char(res, sep_commands[i], 1);
				i++;
			}
		}
		else if (sep_commands[i] == '\"')
		{
			i++;
		}
		else if (sep_commands[i] == '\'')
		{
			tmp = extract_from_quotes(sep_commands, i);
			if (tmp)
			{
				res = ft_concat(res, tmp);
				i += (ft_strlen_modif(tmp) + 2);
			}
			else
			{
				tmp = ft_substr(sep_commands, i, ft_strlen_modif(sep_commands) - i); //mb +1 need for 2 and 3 args
				res = ft_concat(res, tmp);
				i += ft_strlen_modif(tmp);
			}
		}
		else if (sep_commands[i] == '$')
		{
			key = extract_key(sep_commands, ++i);
			printf("key ------ %s\n", key);
			if (key != NULL)
			{
				tmp = find_value_in_export(key, head);
				printf("tmp ------ %s\n", tmp);
				i += ft_strlen_modif(key);
				res = ft_concat(res, tmp);
			}
			else
			{
				i++;
				printf("Error: fucked up extracting key\n");
			}
		}
		else
		{
			res = ft_strnjoin_char(res, sep_commands[i], 1);
			i++;
		}
	}
	res = ft_strnjoin_char(res, sep_commands[i], 1);
	printf("res = |%s|\n", res);
	return (res);
}