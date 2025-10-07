/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/25 15:01:56 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/07 15:56:08 by owhearn       ########   odam.nl         */
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

# define DELIMS 	" \t\r\n\v\f"
# define SPACE		' '
# define S_Q		39
# define D_Q		34
# define EOF_SQ		"unexpected EOF while looking for matching \'\n"
# define EOF_DQ		"unexpected EOF while looking for matching \"\n"

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

typedef struct s_commands
{
	char				**args;
	char				*infile_s;
	char				*outfile_s;
	int					infile;
	int					outfile;
	struct s_commands	*next;
	struct s_commands	*prev;
}			t_commands;

typedef struct s_data
{
	char			*input;
	t_cdllist		*envp_copy;
	int				exit_code;
	t_lexer			*lexer;
	t_commands		*commands;
	struct s_data	*next;
	struct s_data	*prev;
}			t_data;

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
void		clear_commands(t_commands *list);

/*setup_commands.c*/
int			build_command_list(t_data *data);

/*concatonate_strings*/
bool		is_quotes(char c);
bool		concatonate_strings(t_lexer *list);

/*concatonate_utils.c*/
bool		is_quotes(char c);
char		*identify_quotes(char c);
int			trim_quotes(t_lexer *node);

/*expand_args.c/expand_utils.c*/
bool		expand_args(t_data *data);
bool		check_env_char(char c);
int			find_dollar_sign(char *str);
int			find_var_size(char *str);

/*lexer_list_clear.c*/
void		lex_del_node(t_lexer *node);
void		lex_del_first(t_data *data);
void		clear_lexer(t_data *data);

/*lexer_list.c*/
t_lexer		*new_lex_node(char *str);
t_lexer		*lex_last(t_lexer *list);
void		lex_add_back(t_lexer **list, t_lexer *new);
int			add_lex_node(char *str, t_lexer **lexer);

/*lexer.c*/
size_t		ft_strlen_delim(char *str, char delim);
char		*strcpy_delim(char *str, char delim1, char delim2, char delim3);
bool		setup_lexer(t_data *data);

/*handle_append.c*/
bool		handle_append(t_commands *list, t_lexer *node);

/*handle_heredoc.c*/
bool		handle_heredoc(t_commands *list, t_lexer *node);

/*handle_input.c*/
int			close_existing_fd(t_commands *list);
bool		handle_input(t_commands *list, t_lexer *node);

/*handle_output.c*/
bool		handle_output(t_commands *list, t_lexer *node);

/*parsing.c*/
int			is_whitespace(char c);
bool		parse_input(t_data *data, char *str);

/*set_redirect*/
bool		set_redirect(t_commands *list, t_lexer *lexer);

/*exit_error.c*/
void		todo_exit(t_data *data);
void		free_structs(t_data *data, t_commands *list);

/*signals.c*/
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);

/*tokeniser.c*/
bool		assign_type(t_data *data);

/*utils.c*/
void		ft_free(char *s);
bool		find_matching_quotes(char *str, bool s_q, bool d_q);

#endif