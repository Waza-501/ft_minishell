/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:57 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/20 10:29:31 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

int	close_heredoc(t_files *list, int *fd)
{
	printf("close data: %s   %i\n", list->filename, *fd);
	if (close(*fd))
		print_close_fd_error();
	if (unlink(list->filename))
		print_remove_hd_error(list->filename);
	return (0);
}

int	close_existing_fd_in(t_files *list, int *fd)
{
	t_files	*copy;

	if (!list->prev)
		return (0);
	copy = find_open_fd(list);
	printf("close existing fd data: %s   %i\n", list->filename, *fd);
	if (list->type == HEREDOC)
		close_heredoc(copy, fd);
	else
		if (close(*fd))
			print_close_fd_error();
	copy->open = false;
	*fd = -1;
	return (0);
}

int	handle_input(t_files *list, int *fd)
{
	if (!list)
		return (0);
	printf("open fd data: %s   %i\n", list->filename, *fd);
	if (close_existing_fd_in(list, fd))
		return (1);
	*fd = open(list->filename, O_RDONLY);
	if (*fd == -1)
		return (infile_open_error(list));
	list->open = true;
	return (0);
}
