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
			fd = open(file_name, O_RDONLY); //какой корректно юзать?
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

void make_command_elems(t_mini *s, int iter_pipes)
{
	int 	iter_elems;
	char	*tmp;

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
}

void make_pipes(t_mini *s)
{
	int iter_pipes;

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
		make_command_elems(s, iter_pipes);
		//ЗАКИДЫВАЮ В MASS3D И НАЧИНАЕМ КВН
		(s->mass3d)[iter_pipes] = s->command_elems; //free
		iter_pipes++;
	}
}

void	ft_parser(t_mini *s, char *line, char **env)
{
	int		iter_commands;

	//ДРОБИМ НА КОМАНДЫ
	s->commands = ft_split_new(line, ';');
	if (NULL == s->commands)
		printf("malloc error: can't allocate for s->commands\n");
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
		
		//Сортировка пайпов, определение всех fd, заполнение массивов по fd
		ft_sort_pipes(s);

<<<<<<< HEAD:parser2.c
		//цикл по коммандам с пайпов
		iter_pipes = 0;
		while ((s->pipes)[iter_pipes])
		{
			//ОПРЕДЕЛЯЕМ FD IN & OUT
			define_fd_out(s, (s->pipes)[iter_pipes]);
			(s->array_fdout)[iter_pipes] = s->fdout;
			// printf("%d\n", (s->array_fdout)[iter_pipes]);
			define_fd_in(s, (s->pipes)[iter_pipes]);
			(s->array_fdin)[iter_pipes] = s->fdin;
			// printf("%d\n", (s->array_fdin)[iter_pipes]);

			//ИЗВЛЕЧЕНИЕ СТРОКИ БЕЗ РЕДИРЕКТОВ
			s->pipes[iter_pipes] = extract_command(s->pipes[iter_pipes], '>'); //free можно внутри extract сделать
			s->pipes[iter_pipes] = extract_command(s->pipes[iter_pipes], '<'); //free

			//РАЗБИЕНИЕ И ЗАМЕНА ЭЛЕМЕНТОВ
			s->command_elems = ft_split_new((s->pipes)[iter_pipes], ' '); 
			iter_elems = 0;
			while ((s->command_elems)[iter_elems])
			{
				// printf("line |%s|\n", s->command_elems[iter_elems]);
				tmp = (s->command_elems)[iter_elems];
				// printf("tmp |%s|\n", tmp);
				(s->command_elems)[iter_elems] = make_substitute((s->command_elems)[iter_elems], &(s->head)); 
				// ft_memdel_1d(tmp);
				// free(tmp);
				// tmp = NULL;
				iter_elems++;
			}

			//ЗАКИДЫВАЮ В MASS3D И НАЧИНАЕМ КВН
			(s->mass3d)[iter_pipes] = s->command_elems; //free
			//if (ft_strlen_modif((s->pipes)[iter_pipes]) > 0)
			//{
			//	sort_ft(s, env);
			//}
			iter_pipes++;
		}
		ft_memdel_2d((void**)s->pipes);
		// (s->array_fdout)[iter_pipes] = -1;
		// (s->array_fdin)[iter_pipes] = -1;
		// int j = 0;
		// while (s->array_fdout[j])
		// {
		// 	printf("%d\n", s->array_fdout[j]);
		// 	j++;
		// }
=======
		//цикл по коммандам с пайпов, внутри разбиение по пробелам и замены
		make_pipes(s);

		//проверка исполняемых файлов
>>>>>>> chingis:parser/parser1.c
		if (ft_strlen_modif((s->commands)[iter_commands]) > 0)
			sort_ft(s, env);
<<<<<<< HEAD:parser2.c
		}
		// ft_memdel_2d((void**)s->array_fdin); 
		// ft_memdel_2d((void**)s->array_fdout);
		iter_commands++;
	}
	ft_memdel_2d((void**)s->commands); // added
=======
		iter_commands++;
	}
>>>>>>> chingis:parser/parser1.c
}