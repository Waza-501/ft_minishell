/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 13:28:02 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/26 11:25:54 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libraries/cd_ll/headers/cd_ll.h"
# include <sys/types.h> /*waitpid*/
# include <sys/wait.h>  /*waitpid*/

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
}						t_token_type;

typedef struct s_lexer
{
	int					id;
	t_token_type		type;
	char				*string;
	bool				concat;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}						t_lexer;

typedef struct s_files
{
	char				*filename;
	char				*hd_delim;
	t_token_type		type;
	bool				open;
	bool				quoted;
	struct s_files		*next;
	struct s_files		*prev;
}						t_files;

typedef struct s_commands
{
	char				**args;
	int					infile;
	int					outfile;
	t_files				*infiles;
	t_files				*outfiles;
	struct s_commands	*next;
	struct s_commands	*prev;
	int					n;
	pid_t				pid;
	int					pipefd[2];
}						t_commands;

typedef struct s_data
{
	char				*input;
	t_cdllist			*envp_copy;
	t_lexer				*lexer;
	t_commands			*commands;
	int					exit_code;
}						t_data;

/*
 * enviroment variables array
 * stop flag for early termination
 * pointer to main data for env sync
 */
typedef struct s_shell
{
	char				**env;
	t_commands			*cmds;
	bool				stop;
	t_data				*data;
}						t_shell;

/*commands_list_utils.c*/
void					clear_commands(t_data *data);

/*setup_commands.c*/
int						build_command_list(t_data *data);

/*commands_list.c*/
t_commands				*command_list_last(t_commands *list);
void					clear_commands(t_data *data);
int						add_command_node(t_commands **list);

/*lexer_list_utils.c*/
int						merge_nodes(t_data *data, t_lexer *node);
int						insert_new_node(t_lexer *node, char *new, char *str);
void					lex_del_node(t_data *data, t_lexer *node);
void					clear_lexer(t_data *data);

/*lexer_list.c*/
t_lexer					*new_lex_node(char *str);
t_lexer					*lex_last(t_lexer *list);
int						lex_add_next(t_lexer *list, t_lexer *new);
int						lex_add_back(t_lexer **list, t_lexer *new);
int						add_lex_node(char *str, t_lexer **lexer);

/*files_list.c*/
void					delete_files_list(t_commands *cmd);
int						add_file_node(t_files **list, t_lexer *lexer);

/*data.c*/
void					free_data(t_data *data);
int						reset_data(t_data *data, int code);
t_data					*init_data(void);

#endif
