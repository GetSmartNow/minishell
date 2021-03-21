#include "../minishell.h"

int skip_symbol(const char *str, int *symbol_count, char symbol)
{
	int iter;

	iter = 0;
	while (str[iter] && str[iter] == symbol)
	{
		(*symbol_count)++;
		iter++;
	}
	return (iter);
}

int is_quote(char symbol)
{
	if (symbol == '\'' || symbol == '\"')
		return (1);
	return (0);
}


