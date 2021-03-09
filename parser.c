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

int		ft_count_quot(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

char	*extract_from_quotes(char *str)
{
	int		str_len;
	int		count_quot;
	int		i;
	int		j;
	char	*new;


	str_len = ft_strlen_modif(str);
	count_quot = ft_count_quot(str);
	new = (char *)malloc((str_len - count_quot + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' && ((i > 0 && str[i - 1] != '\\') || (i == 0)))
			i++;
		new[j] = str[i];
		j++;
		i++;
	}
	return (new);
}

int		ft_count_shields(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i + 1])
	{
		if (str[i] == '\\' && str[i + 1] == '\\')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

char	*clean_from_shielding(char *str)
{
	int		str_len;
	int		count_shield;
	char	*new;
	int		i;
	int		j;

	str_len = ft_strlen_modif(str);
	count_shield = ft_count_shields(str);
	new = (char *)malloc((str_len - (count_shield * 2) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i + 1] == '\\' && str[i] == '\\')
			i += 2;
		new[j] = str[i];
		j++;
		i++;
	}
	printf("%s\n", new);
	return (new);
}

char	*make_substitute(char *sep_commands, t_mass **head)
{
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
	sep_commands = extract_from_quotes(sep_commands);
	sep_commands = clean_from_shielding(sep_commands);
	while (sep_commands[i])
	{
		if (sep_commands[i] == '\'' && (i > 0 && sep_commands[i - 1] == '\\'))
		{
			while (sep_commands[i])
			{
				if (sep_commands[i] == '$' && (i > 0 && sep_commands[i - 1] != '\\'))
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
						printf("Error: fucked up extracting key\n");
					}
				}
				else if (sep_commands[i] != '\\')
				{
					res = ft_strnjoin_char(res, sep_commands[i], 1);
					i++;
				}
				else
					i++;
			}
		}
		else if (sep_commands[i] == '\'' && ((i > 0 && sep_commands[i - 1] != '\\') || (i == 0)))
		{
			while (sep_commands[++i] != '\'')
			{
				res = ft_strnjoin_char(res, sep_commands[i], 1);
			}
			if (sep_commands[i] == '\'')
				i++;
		}
		else if (sep_commands[i] == '$' && ((i > 0 && sep_commands[i - 1] != '\\') || (i == 0)))
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
				printf("Error: fucked up extracting key\n");
			}
		}
		else if (sep_commands[i] != '\\')
		{
			res = ft_strnjoin_char(res, sep_commands[i], 1);
			i++;
		}
		else
			i++;
	}
	// res = extract_from_quotes(res);
	printf("res ------ %s\n", res);

	return (res);
}