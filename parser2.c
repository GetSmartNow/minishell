

#include "minishell.h"

int	ft_arrlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		i++;
	}
	return (i);
}

// if (type == TRUNC)
//         mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
//     else
//         mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
int		detect_type(char *str, int position)
{
	int	out;

	out	= 0;
	if (str[position] == '>' && str[position + 1] == '>')
		out = 2;
	else if (str[position + 1] != '>')
		out = 3;
	return (out);
}


int		find_redir(char *str, char c)
{
	int		iter;
	int		shield_count;
	int		flag;
	int		pos;
	int		flag2;

	flag2 = 0;
	shield_count = 0;
	iter = 0;
	pos = -1;
	while (str[iter])
	{
		if (str[iter] == '\\')
		{
			shield_count++;
			iter++;
			flag2 = 0;
		}
		else if (str[iter] != '\\' && str[iter] != c)
		{
			if ((str[iter] == '\'' || str[iter] == '\"') && shield_count % 2 == 1)
			{
				flag = 0;
				shield_count = 0;
			}
			else if ((str[iter] == '\'' || str[iter] == '\"') && shield_count % 2 != 1)
			{
				flag = 1;
				shield_count = 0;
			}
			iter++;
			if (str[iter] == c && (flag == 1 || shield_count % 2 == 1))
			{
				iter++;
			}
			flag2 = 0;
		}
		else if (str[iter] == c && shield_count % 2 == 1)
		{
			iter++;
			shield_count = 0;
			flag2 = 0;
		}
			// else if (str[iter] == c && !flag2)
			// {
			// 	pos = iter;
			// 	flag2 = 1;
			// 	iter++;
			// }
			// else if (str[iter] == c && flag2 == 1)
			// {
			// 	iter++;
			// 	flag2 = 0;
			// }
		else if (str[iter] == c)
		{
			pos = iter;
			while (str[iter] == c)
			{
				iter++;
				flag2++;
			}
			if (flag2 > 2 && c == '>')
				printf("error wrong symbol with %c\n", c);
			if (flag2 > 1 && c == '<')
				printf("error wrong symbol with %c\n", c);
			return (pos);
		}
	}
	return (pos);
}


char	*find_file_name(char *line, int position, int *len)
{
	int	counter;
	int	start;

	counter = 0;

	while (!ft_isalnum(line[position])) //возможно другой скип нужен, только пробелов
	{
		position++;
		*len += 1;
	}	
	start = position;
	while (ft_isalnum(line[position]) || line[position] == '.')
	{
		counter++;
		position++;
		*len += 1;
	}
	return (ft_substr(line, start, counter));
}

void	define_fd_out(t_mini *s, char *line)
{
	int		position;
	int		fd_type;
	char	*file_name;
	int		iter;
	int		len;

	iter = 0;
	s->fdout = -1;
	while (line[iter])
	{
		position = find_redir(line + iter, '>');
		if (position >= 0)
		{
			file_name = find_file_name(line + iter, position, &len);
			fd_type = detect_type(line + iter, position);
			if (fd_type == 2)
				s->fdout = open(file_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
			else if (fd_type == 3)
				s->fdout = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			iter += position + 1;
		}
		else
		{
			if (s->fdout == -1)
				s->fdout = STDOUT;
			break ;
		}
	}

	//do free
}

void	define_fd_in(t_mini *s, char *line)
{
	int		position;
	char	*file_name;
	int		iter;
	int		fd;
	int		len;

	iter = 0;
	while (line[iter])
	{
		position = find_redir(line + iter, '<');
		if (position >= 0)
		{
			file_name = find_file_name(line + iter, position, &len);
			fd = open(file_name, O_RDONLY);
			if (fd < 0)
				printf("input file error\n");
			else
				s->fdin = fd;
			iter += position + 1;
		}
		else
		{
			s->fdin = STDIN;
			break ;
		}
	}
	
}

char	*extract_command(char *line)
{
	int		len;
	char	*res;
	int		iter;
	int		position;

	iter = 0;
	len = 0;
	res = ft_strdup("");
	while (line[iter])
	{
		position = find_redir(line + iter, '>');
		if (position >= 0)
		{
			find_file_name(line + iter, position, &len);
			// if (position - 1 > 0)
			res = ft_strjoin(res, ft_substr(line, iter, position - 1)); // -1 точно?
			iter += len + 1;
		}
		else
			return (line);
	}

}

void	ft_parser(t_mini *s, char *line, char **env)
{
	int		iter_commands;
	int		iter_pipes;
	int		iter_elems;
	char	*tmp;

	iter_commands = 0;
	s->commands = ft_split_new(line, ';');
	while ((s->commands)[iter_commands])
	{
//		s->pipe.count_pipe = ft_count_pipe((s->commands)[iter_commands]);
		s->pipes = ft_split_new((s->commands)[iter_commands], '|');
		s->pipe.count_pipe = ft_arrlen(s->pipes) - 1;
		s->mass3d = (char ***)malloc((s->pipe.count_pipe + 1) * sizeof(char **));
		iter_pipes = 0;
		while ((s->pipes)[iter_pipes])
		{
			define_fd_out(s, (s->pipes)[iter_pipes]);
			define_fd_in(s, (s->pipes)[iter_pipes]);
			//ИЗВЛЕЧЕНИЕ СТРОКИ БЕЗ РЕДИРЕКТОВ
			//s->pipes[iter_pipes] = extract_command(s->pipes[iter_pipes]);
			s->command_elems = ft_split_new((s->pipes)[iter_pipes], ' '); 
			iter_elems = 0;
			while ((s->command_elems)[iter_elems])
			{
				tmp = (s->command_elems)[iter_elems];
				(s->command_elems)[iter_elems] = make_substitute((s->command_elems)[iter_elems], &(s->head));
				iter_elems++;
				free(tmp);
				tmp = NULL;
			}
			(s->mass3d)[iter_pipes] = s->command_elems; //s->command_elems потеря указателя
			if (ft_strlen_modif((s->pipes)[iter_pipes]) > 0)
			{
				sort_ft(s, env);
			}
			iter_pipes++;
		}
		iter_commands++;
	}
	ft_memdel_1d(line);
}