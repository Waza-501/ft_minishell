/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 10:12:26 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/25 12:03:27 by owhearn       ########   odam.nl         */
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

static int	open_fd_in_order(t_files *list, int *fd)
{
	t_files	*copy;
	int		ret;

	copy = list;
	ret = 0;
	while (copy)
	{
		if (copy->type == INPUT)
		{
			if (handle_input(copy, fd, &ret))
				return (ret);
		}
		else if (copy->type == HEREDOC)
		{
			if (handle_heredoc(copy, fd, &ret))
				return (ret);
		}
		else
		{
			if (handle_output(copy, fd, &ret))
				return (ret);
		}
		copy = copy->next;
	}
	return (ret);
}

int	set_fd_execution(t_shell *shell, t_commands *cmd)
{
	int	fd;
	int	code;

	fd = -1;
	code = open_fd_in_order(cmd->infiles, &fd);
	if (code)
	{
		if (code == 1)
			shell->data->exit_code = 1;
		return (1);
	}
	cmd->infile = fd;
	fd = -1;
	code = open_fd_in_order (cmd->outfiles, &fd);
	if (code)
	{
		shell->data->exit_code = 1;
		return (1);
	}
	cmd->outfile = fd;
	return (0);
}
