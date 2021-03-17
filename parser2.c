

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
		else if (str[iter] == c && !flag2)
		{
			pos = iter;
			flag2 = 1;
			iter++;
		}
		else if (str[iter] == c && flag2 == 1)
		{
			iter++;
		}
	}
	return (pos);
}

void	define_fd_out(t_mini *s, char *line)
{
	int		position;
	int		fd_type;

	position = find_redir(line, '>');
	fd_type = detect_type(line, position);

	//do free
}

//int 	ft_count_pipe(char *str)
//{
//	int i;
//	int flag;
//	int pipes_count;
//
//	i = 0;
//	pipes_count = 0;
//	flag = 0;
//	while (str[i])
//	{
//		if (str[i] == '\"' || str[i] == '\'')
//		{
//			flag = 1;
//		}
//		if (!flag && str[i] == '|')
//		{
//			if (i > 0 && )
//		}
//		i++;
//	}
//	return (pipes_count);
//}

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
		s->mass3d = (char ***)malloc((s->pipe.count_pipe + 1) * sizeof(char **));
		define_fd_out(s, (s->commands)[iter_commands]);
		s->pipes = ft_split_new((s->commands)[iter_commands], '|');
		s->pipe.count_pipe = ft_arrlen(s->pipes) - 1;
		iter_pipes = 0;
		while ((s->pipes)[iter_pipes])
		{
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