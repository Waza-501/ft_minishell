/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 15:22:19 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/05 10:15:43 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "structs.h"

/*files_list.c*/
t_files		*get_last_file(t_files *list);
void		delete_files_list(t_commands *cmd);
int			add_file_node(t_files **list, t_lexer *lexer);

/*handle_append.c*/
bool		handle_append(t_data *data, t_commands *list, t_lexer *node);

/*handle_heredoc.c*/
bool		handle_heredoc(t_data *data, t_commands *list, t_lexer *node);

/*handle_input.c*/
int			close_existing_fd_in(t_commands *list);
bool		handle_input(t_data *data, t_commands *list, t_lexer *node);

/*handle_output.c*/
int			close_existing_fd_out(t_commands *list);
bool		handle_output(t_data *data, t_commands *list, t_lexer *node);

/*set_redirect*/
//bool		set_redirect(t_data *data, t_commands *list, t_lexer *lexer);
int			simplified_redir(t_data *data, t_commands *list, t_lexer *node);


#endif