/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 10:12:26 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/10 12:57:17 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "redirect.h"

int	simplified_redir(t_data *data, t_commands *list, t_lexer *node)
{
	bool	quotes;

	quotes = false;
	if (node->type == INPUT || node->type == HEREDOC)
	{
		if (node->type == HEREDOC)
		{
			if (is_quoted(node->string))
				remove_quotes(data, node);
			quotes = true;
		}
		if (add_file_node(&list->infiles, node))
			malloc_error(data, false);
		get_last_file(list->infiles)->quoted = quotes;
	}
	else if (node->type == OUTPUT || node->type == APPEND)
	{
		if (add_file_node(&list->outfiles, node))
			malloc_error(data, false);
	}
	return (0);
}

static int	open_fd_in_order(t_data *data, t_files *list, int *fd)
{
	t_files	*copy;

	copy = list;
	while (copy)
	{
		if (copy->type == INPUT)
		{
			if (handle_input(data, list, fd))
				return (1);
		}
		else if (copy->type == HEREDOC)
		{
			if (handle_heredoc(data, list, fd))
				return (1);
		}
		else
		{
			if (handle_output(list, fd))
				return (1);
		}
		copy = copy->next;
	}
	return (0);
}

int	set_fd_execution(t_data *data, t_commands *cmd)
{
	int	fd;
	int	code;

	fd = -1;
	code = open_fd_in_order(data, cmd->infiles, &fd);
	if (print_error_fd(code))
		return (1);
	cmd->infile = fd;
	fd = -1;
	code = open_fd_in_order(data, cmd->outfiles, &fd);
	if (print_error_fd(code))
		return (1);
	cmd->outfile = fd;
	return (0);
}
