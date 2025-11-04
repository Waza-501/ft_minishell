/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/25 15:01:56 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 09:04:23 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include "../libraries/cd_ll/headers/cd_ll.h"
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h> /* LONG_MAX */
# include <signal.h> /* SIQQUIT, SIGINT*/
#include <sys/types.h> /*waitpid*/
#include <sys/wait.h> /*waitpid*/

# define DELIMS 	" \t\r\n\v\f"
# define SPACE		' '
# define S_Q		39
# define D_Q		34
# define EOF_SQ		"unexpected EOF while looking for matching \'\n"
# define EOF_DQ		"unexpected EOF while looking for matching \"\n"
# define SYNTAX		"syntax error near unexpected token "
# define SYNTAX_EOF	"syntax error: unexpected end of file\n"

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/*global variable*/
extern int		g_exit_code;

typedef enum e_token_type
{
	EMPTY = 0,
	ARG,
	NOEXPAND,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
}	t_token_type;

typedef struct s_lexer
{
	int				id;
	t_token_type	type;
	char			*string;
	bool			concat;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}			t_lexer;

typedef struct s_files
{
	char			*filename;
	t_token_type	type;
	struct s_files	*next;
	struct s_files	*prev;
}			t_files;

typedef struct s_commands
{
	char				**args;
	char				*infile_s;
	char				*outfile_s;
	int					infile;
	int					outfile;
	t_files				*infiles;
	t_files				*outfiles;
	bool				hd;
	struct s_commands	*next;
	struct s_commands	*prev;
	int					n; // command number in pipeline
	pid_t				pid; //process id when executed
	int					pipefd[2]; //pipe file descriptors (read, write)
}			t_commands;

typedef struct s_data
{
	char			*input;
	t_cdllist		*envp_copy;
	t_lexer			*lexer;
	t_commands		*commands;
	int				exit_code;
	struct s_data	*next;
	struct s_data	*prev;
}			t_data;

typedef struct s_shell
{
	char		**env; //enviroment variables array
	t_commands	*cmds;
	bool		stop; //stop flag for early termination
}			t_shell;

/*TEMPORARY*/
void		print_tokenlist(t_lexer *list);
void		print_command_list(t_commands *list);

/*copy_env*/
t_cdllist	*copy_envp(char **envp);

/*commands_list.c*/
t_commands	*init_commands(void);
t_commands	*command_list_last(t_commands *list);
int			add_command_node(t_commands	**list);

/*commands_list_utils.c*/
void		clear_commands(t_data *data);

/*setup_commands.c*/
int			build_command_list(t_data *data);

/*concatonate_strings*/
int			merge_nodes(t_lexer *node);
bool		is_quotes(char c);
bool		concatonate_strings(t_data *data);

/*concatonate_utils.c*/
bool		is_quotes(char c);
char		*identify_quotes(char c);
int			remove_quotes(t_lexer *node);
int			trim_quotes(t_lexer *node);

/*expand_args.c/expand_utils.c*/
bool		expand_args(t_data *data);
bool		check_env_char(char c);
int			find_dollar_sign(char *str);
int			find_var_size(char *str);
int			find_var_in_string(char *str, char *var);
bool		reform_string(t_lexer *node, char *start, char *end, char *middle);

/*lexer_list_utils.c*/
int			insert_new_node(t_lexer *node, char *new, char *str);
void		lex_del_node(t_lexer *node);
void		lex_del_first(t_data *data);
void		clear_lexer(t_data *data);

/*lexer_list.c*/
t_lexer		*new_lex_node(char *str);
t_lexer		*lex_last(t_lexer *list);
int			lex_add_next(t_lexer *list, t_lexer *new);
int			lex_add_back(t_lexer **list, t_lexer *new);
int			add_lex_node(char *str, t_lexer **lexer);

/*lexer_utils.c*/
size_t		ft_strlen_delim(char *str, char delim);
char		*strcpy_delim(char *str, char delim1, char delim2, char delim3);

/*lexer.c*/
bool		setup_lexer(t_data *data);

/*handle_append.c*/
bool		handle_append(t_data *data, t_commands *list, t_lexer *node);

/*handle_heredoc.c*/
bool		handle_heredoc(t_data *data, t_commands *list, t_lexer *node);

/*handle_input.c*/
int			close_existing_fd_in(t_data *data, t_commands *list);
bool		handle_input(t_data *data, t_commands *list, t_lexer *node);

/*handle_output.c*/
int			close_existing_fd_out(t_data *data, t_commands *list);
bool		handle_output(t_data *data, t_commands *list, t_lexer *node);

/*parsing.c*/
int			is_whitespace(char c);
int			parse_input(t_data *data, char *str);

/*set_redirect*/
bool		set_redirect(t_data *data, t_commands *list, t_lexer *lexer);

/*error_print.c*/
void		print_syntax_error(char *msg, char *token);
void		print_error(char *msg);
void		*malloc_error_print(char *msg);

/*error.c*/
void		todo_exit(t_data *data);
void		free_structs(t_data *data);
void		perror_exit(t_data *data);
void		*malloc_error(t_data *data, bool print);

/*signals.c*/
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);

/*tokeniser.c*/
bool		assign_type(t_data *data);

/*utils.c*/
void		ft_free(void *ptr);
bool		find_matching_quotes(char *str, bool s_q, bool d_q);

/*main.c*/
int			reset_data(t_data *data, int code);

// Updated function prototypes Max
bool        is_builtin(t_commands *cmd);
int         execute_builtin(t_commands *cmd, t_shell *shell);
void        ft_execve(t_commands *cmd, t_shell *shell, char **path);
void        ft_waitpid(t_shell *shell);
bool        single_cmd(t_shell *shell);
void        execute(t_shell *shell);

// Updated builtin prototypes Max
int         ft_echo(t_commands *cmd);
int         ft_cd(t_commands *cmd, t_shell *shell);
int         ft_export(t_commands *cmd, t_shell *shell, char *str);
int         ft_unset(t_commands *cmd, t_shell *shell);
int         ft_exit(t_commands *cmd);
int		 	ft_pwd(void);
int		 	ft_env(char **env);
int    		modify_path(t_shell *shell, char *temp, int code, int code2);
char        *get_pwd(void);
void		check_and_send(t_shell *shell, char *str);

// Executor - Bridge functions Max
int         execute_commands(t_data *data);
int         init_shell_for_execution(t_shell *shell, t_data *data);
char        **convert_cdll_to_env_array(t_cdllist *env_list);
void        cleanup_shell(t_shell *shell);
void	ft_dup2(int fd1, int fd2);
pid_t	ft_fork(void);
void	ft_pipe(int fd[2]);
int	ft_dup(int fd);
void	ft_waitpid(t_shell *shell);

int	add_file_node(t_files **list, t_lexer *lexer);

#endif