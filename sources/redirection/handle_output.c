/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_output.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:55 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/17 14:09:35 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

int	close_existing_fd_out(t_files *list, int *fd)
{
	if (!list->prev)
		return (0);
	if (close(*fd))
		print_close_fd_error();
	*fd = -1;
	list->prev->open = false;
	return (0);
}

int	handle_output(t_files *list, int *fd)
{
	if (!list)
		return (0);
	if (close_existing_fd_out(list, fd))
		return (false);
	if (list->type == OUTPUT)
		*fd = open(list->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*fd = open(list->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (outfile_open_error(list));
	list->open = true;
	return (0);
}
