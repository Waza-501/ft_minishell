/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 10:12:26 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/05 15:19:35 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

int	simplified_redir(t_data *data, t_commands *list, t_lexer *node)
{
	if (node->type == INPUT || node->type == HEREDOC)
	{
		if (add_file_node(&list->infiles, node))
			malloc_error(data, false);
	}
	else if (node->type == OUTPUT || node->type == APPEND)
	{
		if (add_file_node(&list->outfiles, node))
			malloc_error(data, false);
	}
	return (0);
}

static int	open_fd_in_order(t_commands *cmd, t_files *list, int *fd)
{
	t_files	*copy;

	copy = list;
	while (copy)
	{
		// if (copy->type == INPUT || copy->type == HEREDOC)
		// {
		// 	if (handle_input_new())
		// 		return (1);
		// }
		// else
		// {
		// 	if (handle_output_new())
		// 		return (1);
		// }
		copy = copy->next;
	}
	return (0);
}

int	set_fd_execution(t_commands	*cmd)
{
	int	fd;
	int	code;

	fd = -1;
	code = open_fd_in_order(cmd, cmd->infiles, &fd);
	//if (print_error_fd(code))
		//return (1);
	cmd->infile = fd;
	fd = -1;
	code = open_fd_in_order(cmd, cmd->outfiles, &fd);
	//if (print_error_fd(code))
		//return (1);
	cmd->outfile = fd;
	return (0);
}
