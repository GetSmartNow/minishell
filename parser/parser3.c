/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:49:51 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/22 02:44:03 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_strlen_modif(const char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnjoin_char(char *s1, char c, int quantity)
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
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (quantity--)
		result[i++] = c;
	result[i] = '\0';
	ft_memdel_1d(s1);
	return (result);
}

char	*ft_concat(char *str1, char *str2)
{
	int		len;
	int		i;
	int		j;
	char	*res;

	len = ft_strlen_modif(str1) + ft_strlen_modif(str2) + 1;
	res = (char *)malloc(len * sizeof(char));
	if (NULL == res)
		return (NULL);
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
	ft_memdel_1d(str1);
	ft_memdel_1d(str2);
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

int	ft_isspace(char c)
{
	int	result;

	result = 0;
	if (c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r' || c == ' ')
		result = 1;
	return (result);
}

int		ft_isemptystr(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return 0;
		str++;
	}
	return (1);
}

void add_simple_char(char c, int *i, char **res, int counter)
{
	if (counter == 0)
	{
		(*res) = ft_strnjoin_char((*res), (char)ft_tolower(c), 1);
		(*i)++;
	}
	else
	{
		(*res) = ft_strnjoin_char((*res), c, 1);
		(*i)++;
	}
}

void errno_handler(const char *command, int *i, char **res)
{
	if (!ft_strncmp(command, "$?", 3))
		(*res) = ft_concat((*res), ft_strdup("$?"));
	else
		(*res) = ft_concat((*res), ft_itoa(g_sig.exit_status));
	(*i) += ft_strlen_modif("$?");
}

void replace(char *command, t_mass **head, int *i, char **res)
{
	char	*key;
	char	*tmp;

	key = extract_key(command, ++(*i));
	if (NULL != key)
	{
		tmp = find_value_in_export(key, head);
		(*i) += ft_strlen_modif(key);
		if (NULL != tmp && ft_strcmp(tmp, ""))
			(*res) = ft_concat((*res), tmp);
		ft_memdel_1d(key);
	}
	else
		(*i)++;
}

int if_shield(const char *command, int *count_shield, int *i, char **res)
{
	(*i) += skip_symbol(command + (*i), count_shield, '\\');
	if ((*count_shield) >= 2)
	{
		(*res) = ft_strnjoin_char((*res), '\\', (*count_shield) / 2);
	}
	if (is_shielded(command[(*i)]) && (*count_shield) % 2 == 1)
	{
		(*res) = ft_strnjoin_char((*res), command[(*i)], 1);
		(*i)++;
	}
	(*count_shield) = 0;
	return (-1);
}

int if_single_quote(char *command, t_mini *s, int *i, char **res)
{
	char *tmp;

	tmp = extract_from_quotes(command, (*i)); //no need in free cause of concat
	if (tmp)
	{
		(*res) = ft_concat((*res), tmp);
		(*i) += (ft_strlen_modif(tmp) + 2); //сомневаюсь насчет 2, но пока до сих пор работает
	}
	else
		paste_error("quote is not closed\n", s);
	return (-1);
}

int if_dollar(char *command, t_mass **head, int *i, char **res)
{
	if (!ft_strncmp(command + (*i), "$?", 2))
		errno_handler(command + (*i), i, res);
	else
		replace(command, head, i, res);
	return (-2);
}

int if_double_quote(int *i, int *flag1)
{
	(*i)++;
	(*flag1)++;
	return (-1);
}

void init_before_replacement(int *i, char **res, int *count_shield, int *flag1)
{
	(*flag1) = 0;
	(*res) = NULL;
	(*i) = 0;
	(*count_shield) = 0;
}

char *make_substitute(char *command, t_mass **head, int counter, t_mini *s)
{
	int		i;
	char	*res;
	int		count_shield;
	int 	flag1;

	init_before_replacement(&i, &res, &count_shield, &flag1);
	while (command[i] && s->err_status == 0)
	{
		if (command[i] == '\\')
			counter = if_shield(command, &count_shield, &i, &res);
		else if (command[i] == '\"')
			counter = if_double_quote(&i, &flag1);
		else if (command[i] == '\'')
			counter = if_single_quote(command, s, &i, &res);
		else if (command[i] == '$')
			counter = if_dollar(command, head, &i, &res);
		else
			add_simple_char(command[i], &i, &res, counter);
	}
	if (flag1 % 2 == 1)
		paste_error("quote is not closed\n", s);
	if (counter != -2 && res == NULL)
		paste_error("malloc error\n", s);
	return (res);
}