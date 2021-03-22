#include "../minishell.h"
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
int		detect_out_redirect_type(const char *str, int position)
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

	while (line[position] && !ft_isalnum(line[position])) //возможно другой скип нужен, только пробелов
	{
		position++;
		*len += 1;
	}	
	start = position;
	while (line[position] && (ft_isalnum(line[position]) || line[position] == '.'))
	{
		counter++;
		position++;
		*len += 1;
	}
	while (line[position] && (ft_isspace(line[position])))
	{
		*len += 1;
		position++;
	}
	return (ft_substr(line, start, counter));
}


int ft_fill_fd(t_mini *s, char *line, char *file_name, int position)
{
	int fd_type;

	fd_type = detect_out_redirect_type(line, position);
	if (s->fdout != -1)
		close(s->fdout);
	if (fd_type == 2)
		s->fdout = open(file_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU); //add check if opened and close previous
	else if (fd_type == 1)
		s->fdout = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (s->fdout < 0)
		paste_error("output file error\n", s);
	return (fd_type);
}

void	define_fd_out(t_mini *s, char *line)
{
	int		position;
	char	*file_name;
	int		iter;
	int		len;

	iter = 0;
	file_name = NULL;
	s->fdout = -1;
	while (line[iter])
	{
		position = find_symbol(line + iter, '>', s);
		if (position >= 0)
		{
			len = 0;
			ft_memdel_1d((void *)file_name);
			file_name = find_file_name(line + iter, position, &len);
			if (NULL == file_name)
				paste_error("malloc error\n", s);
			iter += position + ft_fill_fd(s, line + iter, file_name, position);
		}
		else
		{
			if (s->fdout == -1)
				s->fdout = STDOUT;
			break ;
		}
	}
	ft_memdel_1d((void *)file_name);
}

void	define_fd_in(t_mini *s, char *line)
{
	int		position;
	char	*file_name;
	int		iter;
	int		fd;
	int		len;

	iter = 0;
	//if (s->fdin != -1)
	//	close(s->fdin);
	s->fdin = -1;
	file_name = NULL;
	while (line[iter])
	{
		position = find_symbol(line + iter, '<', s);
		if (position >= 0)
		{
			len = 0;
			ft_memdel_1d((void *)file_name);
			file_name = find_file_name(line + iter, position, &len);
			if (NULL == file_name)
				paste_error("malloc error\n", s);
			if (s->fdin != -1)
				close(s->fdin);
			fd = open(file_name, O_RDONLY); //какой корректно юзать?
			if (fd < 0)
				paste_error("input file error\n", s);
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
	ft_memdel_1d((void *)file_name);
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
	ft_memdel_1d((void *)line);
	return (res);
}

char *extract_command(char *line, char redir, t_mini *s)
{
	int		len;
	char	*res;
	int		iter;
	int		position;
	char	*file_name;

	file_name = NULL;
	iter = 0;
	res = ft_strdup(line);
	if (NULL == res)
		paste_error("malloc error\n", s);
	position = 0;
	while (*res && position >= 0)
	{
		position = find_symbol(res, redir, s);
		if (position >= 0)
		{
			len = 0;
			ft_memdel_1d(file_name);
			file_name = find_file_name(res, position, &len);
			if (NULL == file_name)
				paste_error("malloc error\n", s);
			res = ft_strcut(res, iter + position, len); //love this function, add later to my lib;
		}
	}
	ft_memdel_1d((void *)file_name);
	ft_memdel_1d((void *)line);
	return (res);
}

char *extract_file_name(char *line, char redir, t_mini *s)
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
		position = find_symbol(line + iter, redir, s);
		if (position >= 0)
		{
			len = 0;
			ft_memdel_1d(file_name);
			file_name = find_file_name(line + iter, position, &len);
			if (NULL == file_name)
				paste_error("malloc error\n", s);
			iter += position + 1;
		}
	}
	return (file_name);
}

void make_run_command_elems(t_mini *s, int iter_pipes)
{
	int 	iter_elems;
	char	*tmp;

	s->command_elems = ft_split_new((s->pipes)[iter_pipes], ' ');
	if (NULL == s->command_elems)
		paste_error("malloc error\n", s);
	iter_elems = 0;
	while ((s->command_elems)[iter_elems])
	{
		tmp = (s->command_elems)[iter_elems];
		(s->command_elems)[iter_elems] = make_substitute((s->command_elems)[iter_elems], &(s->head), iter_elems, s);
		ft_memdel_1d((void *)tmp);
		iter_elems++;
	}
}

void run_pipes(t_mini *s)
{
	int 	iter_pipes;

	iter_pipes = 0;
	while ((s->pipes)[iter_pipes])
	{
		s->pipes[iter_pipes] = extract_command(s->pipes[iter_pipes], '>', s);
		if (NULL == s->pipes[iter_pipes])
			paste_error("malloc error\n", s);
		s->pipes[iter_pipes] = extract_command(s->pipes[iter_pipes], '<', s);
		if (NULL == s->pipes[iter_pipes])
			paste_error("malloc error\n", s);
		make_run_command_elems(s, iter_pipes);
		(s->mass3d)[iter_pipes] = s->command_elems;
		iter_pipes++;
	}
}

void	paste_error(const char *str, t_mini *s)
{
	if (s->err_message == NULL)
		s->err_message = ft_strdup(str);
	s->err_status = 1;
}

void	print_error(t_mini *s)
{
	write(STDERR, "bash: ", 6);
	write(STDERR, s->err_message, ft_strlen(s->err_message));
}

void 	run_checks(char *str, t_mini *s)
{
	int position;
	int i;

	position = 0;
	i = 0;
	while (str[i] && position >=0)
	{
		position = find_symbol(str + i, '|', s);
		i += position + 1;
	}
	i = 0;
	position = 0;
	while (str[i] && position >=0)
	{
		position = find_symbol(str + i, '>', s);
		i += position + 1;
	}
	i = 0;
	position = 0;
	while (str[i] && position >=0)
	{
		position = find_symbol(str + i, '<', s);
		i += position + 1;
	}
}

void free_command(t_mini *s)
{
	int i;

	i = -1;
	while (++i < s->pipe.count_commands)
	{
		ft_memdel_2d((void **)s->mass3d[i]);
	}
	ft_memdel_2d((void **)s->pipes);
	ft_memdel_1d((void *)s->array_fdin);
	ft_memdel_1d((void *)s->array_fdout);
	free(s->mass3d);
	s->mass3d = NULL;
}

void prepare_for_pipes(t_mini *s, int iter_commands)
{//ДРОБИМ НА ПАЙПЫ, СЧИТАЕМ ПАЙПЫ, ВЫДЕЛЯЕМ ПОД КОЛИЧЕСТВО ПАЙПОВ ПАМЯТЬ В МАС3Д
	s->pipes = ft_split_new((s->commands)[iter_commands], '|');
	if (NULL == s->pipes)
		paste_error("malloc error\n", s);
	s->pipe.count_pipe = ft_arrlen(s->pipes) - 1;
	s->pipe.count_commands = s->pipe.count_pipe + 1;

	//выделение памяти под мас3д, массивы фдшников
	s->mass3d = (char ***)malloc((s->pipe.count_commands + 1) * sizeof(char **)); //free
	if (NULL == s->mass3d)
		paste_error("malloc error\n", s);
	s->array_fdin = (int *)malloc(ft_arrlen(s->pipes) * sizeof(int));
	if (NULL == s->array_fdin)
		paste_error("malloc error\n", s);
	s->array_fdout = (int *)malloc(ft_arrlen(s->pipes) * sizeof(int));
	if (NULL == s->array_fdout)
		paste_error("malloc error\n", s);
}

void prepare_commands(t_mini *s, const char *line, char **env)
{
	int iter_commands;

	s->commands = ft_split_new(line, ';');
	if (NULL == s->commands)
		paste_error("malloc error\n", s);
	iter_commands = 0;
	while ((s->commands)[iter_commands])
	{
		if (s->err_status == 0)
		{
			prepare_for_pipes(s, iter_commands);
			ft_sort_pipes(s);
			run_pipes(s);
			if (s->err_status)
				print_error(s);
			else if (ft_strlen_modif((s->commands)[iter_commands]) > 0)
				sort_ft(s, env);
			iter_commands++;
			free_command(s);
		}
	}
}

void init_err_info(t_mini *s)
{
	s->err_message = NULL;
	s->err_status = 0;
}

void	ft_parser(t_mini *s, char *line, char **env)
{
	init_err_info(s);
	run_checks(line, s);
	if (s->err_status == 0)
	{
		prepare_commands(s, line, env);
		ft_memdel_2d((void **)s->commands);
	}
	if (s->err_status)
		print_error(s);
}
