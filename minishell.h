/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:20:59 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/22 21:02:38 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/include/libft.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2


typedef struct		s_pipe
{
	int				**fd;
	pid_t			*pid;
	int				count_pipe;
	int				count_commands;
}					t_pipe;

typedef struct		s_mass
{
	void			*content;
	struct s_mass	*next;
	struct s_mass	*prev;
}					t_mass;

typedef struct		s_env
{
	char			*bin;
	int				shlvl;
	int				pwd;
	char			*oldpwd;
	char			*path;
	int				count_bin;
}					t_env;

typedef struct		s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}					t_sig;

typedef struct		s_mini
{
	t_pipe			pipe;
	t_mass			*head;
	t_mass			*head_x;
	t_env			var;
	char			*av;
	char			***mass3d;
	char			**env;
	char			**div_pipe;
	char			*tmp;
	int				ret;
	int				exit;
	char			*free_line;
	
	
	int				err_status;
	char			*err_message;
	int				fdout;
	int				fdin;
	int				*array_fdout;
	int				*array_fdin;
	char 			**command_elems;
	char 			**pipes;
	char 			**commands;

}					t_mini;

t_sig	g_sig;

/*INIT*/
void				ft_init_before_loop(t_mini *s, char *av);
void				ft_init_in_loop(t_mini *s);
int					init_list(t_mini *s, char **env);
int					init_list_x(t_mini *s, char **env);

int					exec_bin(t_mini *s, char **arr, char *command);
int					mini_bin(t_mini *s);
void				mini_cd(t_mini *s, char *exec, char *arg);
void				mini_pwd(t_mini	*s);
void				mini_pwd_1(t_mini *s);
void				mini_oldpwd(t_mini *s);
void				mini_echo(char **str, t_mini *s);
int					mini_exit(t_mini *s, char *exec, char *arg);
void				mini_env(t_mini *s);
void				export_to_env(t_mini *s, int i);
void				mini_export(t_mini *s);
void				mini_unset(t_mini *s);
int					mini_pipes(t_mini *s);

/*ENV*/
void				ft_shlvl(t_mini *s);
int					check_shlvl(t_mini *s, char *line, int	sep);
int					mini_atoi(char *line);
void				get_pwd(t_mini	*s);

/*SIGNAL*/
void				init_signal(void);
void				sig_int(int signum);
void				sig_quit(int code);
void				exit_code(t_mini *s);

int					length_to_equal(t_mini *s, char *line);
char				*put_quotes(char *s1);
void				ft_error(char *error, int flag);
char				*mini_putnbr(int n);

t_mass				*my_lstnew(void *content);
void				my_lstadd_back(t_mass **lst, t_mass *new);
void				my_lstdelone(t_mass *lst, void (*del)(void *));
t_mass				*deletelem(t_mass *lst);
void				ft_list_sort(t_mass **lst);
void				sort_ft(t_mini *s, char **env1);


//________________PARSER

/* 
**	parser/find_symbol.c
*/
void ident_bad_dup(char *str, char c, t_mini *s);
void define_flag(int shield_count, int *flag);
void define_flag2(int shield_count, int *flag);
int find_symbol(char *str, char c, t_mini *s);

/* 
**	parser/make_subst.c
*/
char *make_substitute(char *command, t_mass **head, int counter, t_mini *s);

/* 
**	parser/new_split.c
*/
char			**ft_split_new(char const *s, char c);

/* 
**	parser/parser.c
*/
void	ft_parser(t_mini *s, char *line, char **env);
void prepare_commands(t_mini *s, const char *line, char **env);
void prepare_for_pipes(t_mini *s, int iter_commands);
void run_pipes(t_mini *s);
void make_run_command_elems(t_mini *s, int iter_pipes);

/* 
**	parser/sort_pipes.c
*/
void	create_fd(t_mini *s);
void	ft_sort_pipes(t_mini *s);

/* 
**	parser/substitution_if.c
*/
int if_shield(const char *command, int *count_shield, int *i, char **res);
int if_single_quote(char *command, t_mini *s, int *i, char **res);
int if_dollar(char *command, t_mass **head, int *counter, char **res);
// int if_dollar(char *command, t_mass **head, int *i, char **res);
int if_double_quote(int *i, int *flag1);

/* 
**	parser/utils_err.c
*/
void	paste_error(const char *str, t_mini *s);
void	print_error(t_mini *s);
void 	run_checks(char *str, t_mini *s);

/* 
**	parser/utils_fd.c
*/
void	define_fd_in(t_mini *s, char *line);
void	define_fd_out(t_mini *s, char *line);
int ft_fill_fd(t_mini *s, char *line, char *file_name, int position);

/* 
**	parser/utils_init.c
*/
void init_before_replacement(int *i, char **res, int *count_shield, int *flag1);
void init_err_info(t_mini *s);

/* 
**	parser/utils_str.c
*/
char	*ft_strnjoin_char(char *s1, char c, int quantity);
char	*ft_concat(char *str1, char *str2);
void add_simple_char(char c, int *i, char **res, int counter);
// void replace(char *command, t_mass **head, int *i, char **res);
int replace(char *command, t_mass **head, char **res);
// char	*extract_key(char *str, int pos);
char	*extract_key(char *str);

/* 
**	parser/utils_str2.c
*/
char	*ft_strcut(char *line, int start, int len);
char *extract_command(char *line, char redir, t_mini *s);
char *extract_file_name(char *line, char redir, t_mini *s);
char	*find_file_name(char *line, int position, int *len);

/* 
**	parser/utils_subst.c
*/
char	*find_value_in_export(char *key, t_mass **head);
char	*extract_from_quotes(char *str, int pos);
int	is_shielded(char c);
// void errno_handler(const char *command, int *i, char **res);
int errno_handler(const char *command, int *counter, char **res);
/* 
**	parser/utils1.c
*/
int skip_symbol(const char *str, int *symbol_count, char symbol);
int is_quote(char symbol);
int	ft_arrlen(char **matrix);
int	ft_isspace(char c);
int	ft_strlen_modif(const char *str);
/* 
**	parser/utils2.c
*/
void	ft_arr_strswap(char ***str_array, int i, int j);
void	ft_arr_intswap(int **int_array, int i, int j);
void free_command(t_mini *s);
int		detect_out_redirect_type(const char *str, int position);
#endif