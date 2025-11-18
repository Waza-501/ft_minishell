/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:57 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/18 17:50:14 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

int	close_heredoc(t_files *list, int *fd)
{
	printf("close data: %s   %i\n", list->filename, *fd);
	if (close(*fd))
		print_close_fd_error();
	if (unlink(list->prev->filename))
		print_remove_hd_error(list->prev->filename);
	return (0);
}

static int	close_last_fd_in(t_files *list, int *fd)
{
	printf("close last data: %s   %i\n", list->filename, *fd);
	if (list->type == HEREDOC)
		if (unlink(list->filename))
			print_remove_hd_error(list->filename);
	if (close(*fd))
		print_close_fd_error();
	list->open = false;
	*fd = -1;
	return (0);
}

int	close_existing_fd_in(t_files *list, int *fd)
{
	if (!list->prev)
		return (0);
	// if (!list->next)
	// 	return (close_last_fd_in(list, fd));
	if (list->prev->type == HEREDOC)
		close_heredoc(list, fd);
	else
		if (close(*fd))
			print_close_fd_error();
	list->prev->open = false;
	*fd = -1;
	return (0);
}

int	handle_input(t_files *list, int *fd)
{
	if (!list)
		return (0);
	if (close_existing_fd_in(list, fd))
		return (1);
	*fd = open(list->filename, O_RDONLY);
	if (*fd == -1)
		return (infile_open_error(list));
	list->open = true;
	return (0);
}
