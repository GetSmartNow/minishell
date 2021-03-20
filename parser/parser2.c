#include "minishell.h"
//UTILS
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
//UTILS
int		detect_out_redirect_type(char *str, int position)
{
	int	out;

	out	= 0;
	if (str[position] == '>' && str[position + 1] == '>')
		out = 2;
	else if (str[position + 1] != '>')
		out = 1;
	return (out);
}

//СУПЕР ЕРЕСЬ, МБ МОЖНО СОКРАТИТЬ 
int		find_redir(char *str, char c)
{
	int	iter;
	int	shield_count;
	int	position;
	int	flag;
	int	check_flag;

	check_flag = 0;
	iter = 0;
	shield_count = 0;
	position = -1;
	flag = 0;
	while (str[iter])
	{
		while (str[iter] && str[iter] == '\\')
		{
			shield_count++;
			iter++;
		}
		if (str[iter] && (str[iter] == '\'' || str[iter] == '\"') && flag == 0)
		{
			if (shield_count % 2 == 0)
			{
				flag = 1;
			}
			shield_count = 0;
		}
		else if (str[iter] && (str[iter] == '\'' || str[iter] == '\"') && flag == 1)
		{
			if (shield_count % 2 == 0)
			{
				flag = 0;
			}
			shield_count = 0;
		}
		else if (str[iter] == c)
		{
			if (shield_count % 2 == 1)
			{
				flag = 1;
			}
			shield_count = 0;
			if (flag == 0)
			{
				position = iter;
				while (str[iter] && str[iter] == c)
				{
					iter++;
					check_flag++;
				}
				if (c == '<' && check_flag > 1)
					printf("error near <");
				else if (c == '>' && check_flag > 2)
					printf("error near >");
				//else
				//	iter -= check_flag;
				return (position);
			}
		}
		iter++;
	}
	return (position);
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
	while (ft_isspace(line[position]))
	{
		*len += 1;
		position++;
	}
	return (ft_substr(line, start, counter));
}


int ft_fill_fd(t_mini *s, char *line, char *file_name, int position)
{
	int fd_type;

	s->in_file = ft_strdup(file_name); //free
	fd_type = detect_out_redirect_type(line, position);
	if (s->fdout != -1)
		close(s->fdout);
	if (fd_type == 2)
		s->fdout = open(file_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU); //add check if opened and close previous
	else if (fd_type == 1)
		s->fdout = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (s->fdout < 0)
		printf("error in open (ft_fill_fd)\n");
	return (fd_type);
}

void	define_fd_out(t_mini *s, char *line)
{
	int		position;
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
			len = 0;
			file_name = find_file_name(line + iter, position, &len); //free
			iter += position + ft_fill_fd(s, line + iter, file_name, position);
		}
		else
		{
			if (s->fdout == -1)
				s->fdout = STDOUT;
			break ;
		}
	}
}

void	define_fd_in(t_mini *s, char *line)
{
	int		position;
	char	*file_name;
	int		iter;
	int		fd;
	int		len;

	iter = 0;
	s->fdin = -1;
	while (line[iter])
	{
		position = find_redir(line + iter, '<');
		if (position >= 0)
		{
			len = 0;
			file_name = find_file_name(line + iter, position, &len);
			s->from_file = ft_strdup(file_name); //free
			fd = open(file_name, O_RDONLY);
			if (fd < 0)
				printf("input file error\n");
			else
				s->fdin = fd;
			iter += position + 1;
		}
		else
		{
			if (s->fdin == -1)
				s->fdin = STDIN;
			break ;
		}
	}	
}

char	*ft_strcut(char *line, int start, int len)
{
	char	*res;
	int		iter;
	int		i;

	i = 0;
	iter = 0;
	res = ft_strdup("");
	while (iter < start)
	{
		res = ft_strnjoin_char(res, line[i], 1);
		iter++;
		i++;
	}
	iter = 0;
	while (iter < len)
	{
		iter++;
		i++;
	}
	while (line[i])
	{
		res = ft_strnjoin_char(res, line[i], 1);
		i++;
	}
	return (res);
}

char	*extract_command(char *line, char redir)
{
	int		len;
	char	*res;
	int		iter;
	int		position;

	iter = 0;
	res = ft_strdup(line);
	position = 0;
	while (*res && position >= 0)
	{
		position = find_redir(res, redir);
		if (position >= 0)
		{
			len = 0;
			find_file_name(res, position, &len);
			res = ft_strcut(res, iter + position, len); //love this function, add later to my lib;
		}
	}
	return (res);
}

char	*extract_file_name(char *line, char redir)
{
	int		len;
	int		iter;
	int		position;
	char	*file_name;

	iter = 0;
	position = 0;
	file_name = NULL;
	while (line[iter] && position >= 0)
	{
		position = find_redir(line + iter, redir);
		if (position >= 0)
		{
			len = 0;
			file_name = find_file_name(line + iter, position, &len);
			iter += position + 1;
		}
	}
	return (file_name);
}

void	ft_parser(t_mini *s, char *line, char **env)
{
	int		iter_commands;
	int		iter_pipes;
	int		iter_elems;
	char	*tmp;


	//ДРОБИМ НА КОМАНДЫ
	s->commands = ft_split_new(line, ';');
	iter_commands = 0;
	while ((s->commands)[iter_commands])
	{
		//ДРОБИМ НА ПАЙПЫ, СЧИТАЕМ ПАЙПЫ, ВЫДЕЛЯЕМ ПОД КОЛИЧЕСТВО ПАЙПОВ ПАМЯТЬ В МАС3Д
		s->pipes = ft_split_new((s->commands)[iter_commands], '|');
		s->pipe.count_pipe = ft_arrlen(s->pipes) - 1;
		s->pipe.count_commands = s->pipe.count_pipe + 1;

		//выделение памяти под мас3д, массивы фдшников
		s->mass3d = (char ***)malloc((s->pipe.count_pipe + 1) * sizeof(char **)); //free
		s->array_fdin = (int *)malloc(ft_arrlen(s->pipes) * sizeof(int));
		s->array_fdout = (int *)malloc(ft_arrlen(s->pipes) * sizeof(int));
		
		//Сортировка пайпов
		ft_sort_pipes(s);

		//цикл по коммандам с пайпов
		iter_pipes = 0;
		while ((s->pipes)[iter_pipes])
		{
			//---Перенес в сортировку ft_sort_pipes
			//ОПРЕДЕЛЯЕМ FD IN & OUT
			//define_fd_out(s, (s->pipes)[iter_pipes]);
			//(s->array_fdout)[iter_pipes] = s->fdout;
			//printf("%d\n", (s->array_fdout)[iter_pipes]);
			//define_fd_in(s, (s->pipes)[iter_pipes]);
			//(s->array_fdin)[iter_pipes] = s->fdin;
			//printf("%d\n", (s->array_fdin)[iter_pipes]);

			//ИЗВЛЕЧЕНИЕ СТРОКИ БЕЗ РЕДИРЕКТОВ
			s->pipes[iter_pipes] = extract_command(s->pipes[iter_pipes], '>'); //free можно внутри extract сделать
			s->pipes[iter_pipes] = extract_command(s->pipes[iter_pipes], '<'); //free

			//РАЗБИЕНИЕ И ЗАМЕНА ЭЛЕМЕНТОВ
			s->command_elems = ft_split_new((s->pipes)[iter_pipes], ' '); 
			iter_elems = 0;
			while ((s->command_elems)[iter_elems])
			{
				tmp = (s->command_elems)[iter_elems];
				(s->command_elems)[iter_elems] = make_substitute((s->command_elems)[iter_elems], &(s->head), iter_elems); 
				free(tmp);
				tmp = NULL;
				iter_elems++;
			}
			//ЗАКИДЫВАЮ В MASS3D И НАЧИНАЕМ КВН
			(s->mass3d)[iter_pipes] = s->command_elems; //free
			iter_pipes++;
		}
		//ft_memdel_2d((void **)s->pipes);

		

		if (ft_strlen_modif((s->commands)[iter_commands]) > 0)
		{
			sort_ft(s, env);
		}
		iter_commands++;
	}
	//ft_memdel_2d((void **)s->commands);
	//ft_memdel_1d(line); // всё еще сегает
}