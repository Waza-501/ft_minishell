/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 13:28:02 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 18:12:28 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libraries/cd_ll/headers/cd_ll.h"
# include <sys/types.h> /*waitpid*/
# include <sys/wait.h> /*waitpid*/

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

/*commands_list_utils.c*/
void		clear_commands(t_data *data);

/*setup_commands.c*/
int			build_command_list(t_data *data);

/*commands_list.c*/
// t_commands	*init_commands(void);
t_commands	*command_list_last(t_commands *list);
void		clear_commands(t_data *data);
int			add_command_node(t_commands	**list);

/*lexer_list_utils.c*/
int			merge_nodes(t_data *data, t_lexer *node);
int			insert_new_node(t_lexer *node, char *new, char *str);
void		lex_del_node(t_lexer *node);
//void		lex_del_first(t_data *data);
void		clear_lexer(t_data *data);

/*lexer_list.c*/
t_lexer		*new_lex_node(char *str);
t_lexer		*lex_last(t_lexer *list);
int			lex_add_next(t_lexer *list, t_lexer *new);
int			lex_add_back(t_lexer **list, t_lexer *new);
int			add_lex_node(char *str, t_lexer **lexer);

/*files_list.c*/
void		delete_files_list(t_commands *cmd);
int			add_file_node(t_files **list, t_lexer *lexer);

/*data.c*/
void		free_data(t_data *data);
int			reset_data(t_data *data, int code);
t_data		*init_data(void);

#endif