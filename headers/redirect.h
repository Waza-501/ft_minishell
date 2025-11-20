/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 15:22:19 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/20 12:35:56 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "structs.h"

# define HD_EMPTY_LINE "warning, heredoc delimited by EOF: wanted "

/*files_list_utils.c*/
void		close_all_fd(t_commands *cmd);
t_files		*find_open_fd(t_files *list);
void		delete_files_list(t_commands *cmd);
void		print_close_fd_error(void);
void		print_remove_hd_error(char *str);
int			outfile_open_error(t_files *file);
int			infile_open_error(t_files *file);

/*files_list.c*/
t_files		*get_last_file(t_files *list);
t_files		*get_first_file(t_files *list);
int			add_file_node(t_files **list, t_lexer *lexer);

/*handle_append.c*/
int			handle_append(t_files *list, int *fd);

/*heredoc_utils.c*/
char		*get_hd_filename(void);

/*handle_heredoc.c*/
int			handle_heredoc(t_files *list, int *fd);

/*handle_input.c*/
int			close_existing_fd_in(t_files *list, int *fd);
int			handle_input(t_files *list, int *fd);

/*handle_output.c*/
int			close_existing_fd_out(t_files *list, int *fd);
int			handle_output(t_files *list, int *fd);

/*set_redirect*/
//bool		set_redirect(t_data *data, t_commands *list, t_lexer *lexer);
int			simplified_redir(t_data *data, t_commands *list, t_lexer *node);
int			set_fd_execution(t_commands *cmd);

#endif