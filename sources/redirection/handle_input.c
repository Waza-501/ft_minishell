/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:57 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/21 15:29:37 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

int	close_heredoc(t_files *list, int *fd)
{
	close(*fd);
	unlink(list->filename);
	return (0);
}

int	close_existing_fd_in(t_files *list, int *fd)
{
	t_files	*copy;

	if (!list)
		return (0);
	copy = find_open_fd(list);
	if (copy->open == false)
		return (0);
	if (copy->type == HEREDOC)
		close_heredoc(copy, fd);
	else
		close(*fd);
	copy->open = false;
	*fd = -1;
	return (0);
}

int	handle_input(t_files *list, int *fd, int *ret)
{
	if (!list)
		return (0);
	close_existing_fd_in(list, fd);
	*fd = open(list->filename, O_RDONLY);
	if (*fd == -1)
	{
		*ret = infile_open_error(list);
		return (1);
	}
	list->open = true;
	return (0);
}
