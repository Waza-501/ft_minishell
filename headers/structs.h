/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 13:28:02 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 13:31:03 by owhearn       ########   odam.nl         */
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


#endif