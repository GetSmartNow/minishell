/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:39 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/22 15:11:54 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int replace(char *command, t_mass **head, char **res)
{
	char	*key;
	char	*tmp;
	int		i;

	key = extract_key(command);
	if (NULL != key)
	{
		tmp = find_value_in_export(key, head);
		i += ft_strlen_modif(key);
		if (NULL != tmp && ft_strcmp(tmp, ""))
			(*res) = ft_concat((*res), tmp);
		ft_memdel_1d(key);
	}
	else
		i++;
	return (i);
}
// void replace(char *command, t_mass **head, int *i, char **res)
// {
// 	char	*key;
// 	char	*tmp;

// 	key = extract_key(command, ++(*i));
// 	if (NULL != key)
// 	{
// 		tmp = find_value_in_export(key, head);
// 		(*i) += ft_strlen_modif(key);
// 		if (NULL != tmp && ft_strcmp(tmp, ""))
// 			(*res) = ft_concat((*res), tmp);
// 		ft_memdel_1d(key);
// 	}
// 	else
// 		(*i)++;
// }

char	*extract_key(char *str)
{
	char	*res;
	int		pos;

	pos = 0;
	res = NULL;
	if (ft_isdigit(str[pos]))
		return (NULL);
	while (str[pos] && ft_isalnum((int)str[pos]))
	{
		res = ft_strnjoin_char(res, str[pos], 1);
		pos++;
	}
	return (res);
}
// char	*extract_key(char *str, int pos)
// {
// 	char	*res;

// 	res = NULL;
// 	if (ft_isdigit(str[pos]))
// 		return (NULL);
// 	while (str[pos] && ft_isalnum((int)str[pos]))
// 	{
// 		res = ft_strnjoin_char(res, str[pos], 1);
// 		pos++;
// 	}
// 	return (res);
// }