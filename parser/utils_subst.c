/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_subst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:16:26 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/22 15:03:29 by mvernius         ###   ########.fr       */
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

int	is_shielded(char c)
{
	char	*shielded_list;
	int		i;

	shielded_list = "\\\"\'$;";
	i = 0;
	while (shielded_list[i])
	{
		if (shielded_list[i] == c)
			return (1);
		i++;
	}
	return (0);
}



int errno_handler(const char *command, int *counter, char **res)
{
	if (!ft_strncmp(command, "$?", 3))
	{
		if (*counter == 0)
			(*res) = ft_concat((*res), ft_strdup("$?"));
		else
			(*res) = ft_concat((*res), ft_itoa(g_sig.exit_status));
	}
	else
		(*res) = ft_concat((*res), ft_itoa(g_sig.exit_status));
	return (ft_strlen_modif("$?"));
}
// void errno_handler(const char *command, int *i, char **res)
// {
// 	if (!ft_strncmp(command, "$?", 3))
// 		(*res) = ft_concat((*res), ft_strdup("$?"));
// 	else
// 		(*res) = ft_concat((*res), ft_itoa(g_sig.exit_status));
// 	(*i) += ft_strlen_modif("$?");
// }



