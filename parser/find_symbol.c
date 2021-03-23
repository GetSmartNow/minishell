/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_symbol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:17:12 by mvernius          #+#    #+#             */
/*   Updated: 2021/03/24 00:00:56 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ibd_if_block(const char *str, char c, t_mini *s, int iter)
{
	if (str[iter] == '\0')
		paste_error("syntax error near unexpected token `newline\'\n", s);
	else if (!ft_isspace(str[iter]) && !ft_isalnum(str[iter]))
	{
		paste_error("syntax error near unexpected token `", s);
		s->err_message = ft_strnjoin_char(s->err_message, str[iter], 1);
		s->err_message = ft_strnjoin_char(s->err_message, '\'', 1);
		s->err_message = ft_strnjoin_char(s->err_message, '\n', 1);
	}
	else
	{
		if (c == '<' && iter > 1)
			paste_error("syntax error near unexpected token `<\'\n", s);
		else if (c == '>' && iter > 2)
		{
			if (iter == 3)
				paste_error("syntax error near unexpected token `>\'\n", s);
			else
				paste_error("syntax error near unexpected token `>>\'\n", s);
		}
		else if (c == '|' && iter > 1)
			paste_error("syntax error near unexpected token `|\'\n", s);
	}
}

void	ident_bad_dup(char *str, char c, t_mini *s)
{
	int iter;

	iter = 0;
	while (str[iter] && str[iter] == c)
		iter++;
	if (s->err_message == NULL)
	{
		ibd_if_block(str, c, s, iter);
	}
	g_sig.exit_status = 258;
}

void	define_flag(int shield_count, int *flag)
{
	if (shield_count % 2 == 0)
	{
		if ((*flag) == 0)
			(*flag) = 1;
		else
			(*flag) = 0;
	}
	else
		*flag = 1;
}

void	define_flag2(int shield_count, int *flag)
{
	if (shield_count % 2 == 0)
	{
		if ((*flag) == 0)
			(*flag) = 1;
		else
			(*flag) = 0;
	}
}

int		find_symbol(char *str, char c, t_mini *s)
{
	int	iter;
	int	shield_count;
	int	position;
	int	flag;

	init_fs(&iter, &shield_count, &position, &flag);
	while (str[iter])
	{
		iter += skip_symbol(str + iter, &shield_count, '\\');
		if (str[iter] && is_quote(str[iter]))
			define_flag(shield_count, &flag);
		else if (str[iter] == c)
		{
			if (shield_count % 2 == 1)
				flag = 1;
			if (flag == 0)
			{
				ident_bad_dup(str + iter, c, s);
				return (iter);
			}
		}
		shield_count = 0;
		iter++;
	}
	return (position);
}
