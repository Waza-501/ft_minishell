/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:52 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/20 16:21:21 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include "parser.h"
#include "expand.h"
#include "redirect.h"

int	create_hd_file(t_files *list, int *fd)
{
	*fd = open(list->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		ft_putstr_fd(MS_ERROR, STDERR_FILENO);
		ft_putendl_fd("heredoc creation failed.", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	scan_line(char *line, char *delim, bool	quotes)
{
	size_t	size;

	(void)quotes;
	size = ft_strlen(delim);
	if (ft_strlen(line) != size)
		return (0);
	if (!ft_strncmp(line, delim, size))
		return (1);
	return (0);
}

int	fill_heredoc(t_files *list, int *fd)
{
	char	*line;

	line = NULL;
	while (true)
	{
		set_signals_interactive();
		line = readline(">");
		set_signals_noninteractive();
		if (!line)
		{
			ft_putstr_fd(HD_EMPTY_LINE, STDERR_FILENO);
			ft_putendl_fd(list->hd_delim, STDERR_FILENO);
			return (1);
		}
		if (scan_line(line, list->hd_delim, list->quoted))
			break ;
		ft_putendl_fd(line, *fd);
		ft_free(&line);
	}
	ft_free(&line);
	return (0);
}

int	handle_heredoc(t_files *list, int *fd)
{
	if (close_existing_fd_in(list, fd))
		return (1);
	if (create_hd_file(list, fd))
		return (1);
	if (fill_heredoc(list, fd))
		return (1);
	close(*fd);
	*fd = -1;
	*fd = open(list->filename, O_RDONLY);
	if (*fd == -1)
		return (infile_open_error(list));
	list->open = true;
	return (0);
}
