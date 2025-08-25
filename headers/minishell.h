/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/25 15:01:56 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/25 17:17:26 by owhearn       ########   odam.nl         */
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

typedef struct s_token
{
	int				id;
	t_token_type	type;
	char			*string;
	bool			concat;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;

typedef struct s_commands
{
	char				*command;
	char				**args;
	int					infile;
	int					outfile;
	int					type;
	struct s_commands	*next;
	struct s_commands	*prev;
}			t_commands;

typedef struct s_data
{
	char			*input;
	t_cdllist		*envp_copy;
	int				exit_code;
	bool			debug;
	bool			error;
	t_token			*lexer;
	struct s_data	*next;
	struct s_data	*prev;
}			t_data;

/*copy_env*/
t_cdllist	*copy_envp(char **envp);

/*lexer_list.c*/
void		clear_lexer(t_data *data);
t_token		*new_lex_node(char *str);
t_token		*lex_last(t_token *list);
void		lex_add_back(t_token **list, t_token *new);
int			add_lex_node(char *str, t_token **lexer);

/*lexer.c*/
size_t		ft_strlen_delim(char *str, char delim);
char		*strcpy_delim(char *str, char delim);
bool		setup_lexer(t_data *data);

/*parsing.c*/
int			is_whitespace(char c);
bool		parse_input(t_data *data, char *str);

/*signals.c*/
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);

/*tokeniser.c*/
bool		assign_type(t_data *data);

/*utils.c*/
bool		find_matching_quotes(char *str, bool s_q, bool d_q);

#endif