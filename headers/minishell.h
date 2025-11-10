/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/25 15:01:56 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/10 11:44:56 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include "structs.h"
# include "error.h"
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h> /* LONG_MAX */
# include <signal.h> /* SIQQUIT, SIGINT*/
# include <sys/types.h> /*waitpid*/
# include <sys/wait.h> /*waitpid*/

# define DELIMS 	" \t\r\n\v\f"
# define SPACE		' '
# define S_Q		39
# define D_Q		34
# define EOF_SQ		"unexpected EOF while looking for matching \'\n"
# define EOF_DQ		"unexpected EOF while looking for matching \"\n"
# define SYNTAX		"syntax error near unexpected token "
# define SYNTAX_EOF	"syntax error: unexpected end of file\n"
# define MS_ERROR	"minishell: "

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/*global variable*/
extern int		g_exit_code;

/*TEMPORARY*/
void		print_file_list(t_files *files, char *str);
void		print_tokenlist(t_lexer *list);
void		print_command_list(t_commands *list);
void		print_envp(char **envp, t_cdllist *list);

/*copy_env*/
t_cdllist	*copy_envp(char **envp);

/*signals.c*/
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);

/*utils.c*/
void		ft_free(void *ptr);
bool		find_matching_quotes(char *str, bool s_q, bool d_q);

// Updated function prototypes Max
bool		is_builtin(t_commands *cmd);
int			execute_builtin(t_commands *cmd, t_shell *shell);
void		ft_execve(t_commands *cmd, t_shell *shell, char **path);
void		ft_waitpid(t_shell *shell);
bool		single_cmd(t_shell *shell);
void		execute(t_shell *shell);

// Updated builtin prototypes Max
int			ft_echo(t_commands *cmd);
int			ft_cd(t_commands *cmd, t_shell *shell);
int			ft_export(t_commands *cmd, t_shell *shell, char *str);
int			ft_unset(t_commands *cmd, t_shell *shell);
int			ft_exit(t_commands *cmd);
int			ft_pwd(void);
int			ft_env(char **env);
int			modify_path(t_shell *shell, char *temp, int code, int code2);
char		*get_pwd(void);
int			check_and_send(t_shell *shell, char *str);
int			if_exist(char **env, char *str);
void		join_arr(t_shell *shell, char *str);
int			send_arr(t_shell *shell, char *str);
char		**sort_env(char **env);
void		print_env(char **sorted_env);
void		free_sorted_env(char **sorted_env);
char		*ft_getcwd(void);


// Executor - Bridge functions Max
int			execute_commands(t_data *data);
int			init_shell_for_execution(t_shell *shell, t_data *data);
char		**convert_cdll_to_env_array(t_cdllist *env_list);
void		cleanup_shell(t_shell *shell);
void		ft_dup2(int fd1, int fd2);
pid_t		ft_fork(void);
void		ft_pipe(int fd[2]);
int			ft_dup(int fd);
void		ft_waitpid(t_shell *shell);
int			add_file_node(t_files **list, t_lexer *lexer);
int			sync_env_to_list(char **env_array, t_cdllist *env_list);
void        execute_single_command(t_commands *cmd, t_shell *shell, t_data *data);

// Core shell functions (replace existing init/cleanup_shell if you have them)
t_shell     *init_shell(t_data *data);
void        cleanup_shell(t_shell *shell);

// Environment management
int         shell_export(t_shell *shell, char **args);
int         shell_unset(t_shell *shell, char *name);
int         shell_setenv(t_shell *shell, char *name, char *value);

// Sorted environment cache management
void        invalidate_sorted_env(t_shell *shell);
char        **get_sorted_env(t_shell *shell);

// Main loop integration
static int  mini_loop(t_data *data);
void        execute_with_shell(t_shell *shell, t_data *data);
void        execute_other_commands(t_commands *cmd, t_shell *shell, t_data *data);
// Utility functions
char        **quick_parse_args(char *input);
void        free_quick_args(char **args);

#endif
