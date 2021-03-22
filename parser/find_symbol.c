#include "../minishell.h"

void ident_bad_dup(char *str, char c, t_mini *s)
{
	int iter;

	iter = 0;
	while (str[iter] && str[iter] == c)
		iter++;
	if (s->err_message == NULL)
	{
		if (str[iter] == '\0')
			paste_error("syntax error near unexpected token `newline\'\n", s);
		else if (!ft_isspace(str[iter]) && !ft_isalnum(str[iter]))
		{
			paste_error("syntax error near unexpected token `", s);
			s->err_message = ft_strnjoin_char(s->err_message, str[iter], 1);
			s->err_message = ft_strnjoin_char(s->err_message, '\'', 1);
			s->err_message = ft_strnjoin_char(s->err_message, '\n', 1);

			//s->err_message = ft_concat(s->err_message, ft_strdup("\'\n"));
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
	//добавить присвоение 258 ошибки.
}

void define_flag(int shield_count, int *flag)
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

int find_symbol(char *str, char c, t_mini *s)
{
	int	iter;
	int	shield_count;
	int	position;
	int	flag;

	iter = 0;
	shield_count = 0;
	position = -1;
	flag = 0;
	while (str[iter])
	{
		iter += skip_symbol(str + iter, &shield_count, '\\');
		if (str[iter] && is_quote(str[iter]) && flag == 0)
			define_flag(shield_count, &flag);
		else if (str[iter] && is_quote(str[iter]) && flag == 1)
			define_flag(shield_count, &flag);
		else if (str[iter] == c)
		{
			//define_flag(shield_count, &flag);
			if (shield_count % 2 == 1)
				flag = 1;
			if (flag == 0)
			{
				position = iter;
				ident_bad_dup(str + iter, c, s);
				//else
				//	iter -= check_flag;
				return (position);
			}
		}
		shield_count = 0;
		iter++;
	}
	return (position);
}


