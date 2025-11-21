/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_output.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:55 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/21 15:29:32 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

int	close_existing_fd_out(t_files *list, int *fd)
{
	t_files	*copy;

	if (!list)
		return (0);
	copy = find_open_fd(list);
	if (copy->open == false)
		return (0);
	close(*fd);
	copy->open = false;
	*fd = -1;
	return (0);
}

int	handle_output(t_files *list, int *fd, int *ret)
{
	if (!list)
		return (0);
	close_existing_fd_out(list, fd);
	if (list->type == OUTPUT)
		*fd = open(list->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*fd = open(list->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		*ret = outfile_open_error(list);
		return (1);
	}
	list->open = true;
	return (0);
}
