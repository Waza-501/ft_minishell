/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:52 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/06 18:22:30 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include "parser.h"
#include "redirect.h"

int	create_hd_file(t_files *list, int *fd)
{
	*fd = open(list->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		ft_putstr_fd(MS_ERROR, STDERR_FILENO);
		ft_putstr_fd("heredoc creation failed.", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	scan_line(char *line, char *delim)
{
	int	size;

	size = ft_strlen(delim);
	if (is_quoted(delim))
		size -= 2;
	
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
			return (printf("warning", "heredoc delimited by EOF: wanted\n"), 1);
			//exit(1);
		if (scan_line(line, list->hd_delim))
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
	exit (1);
	return (0);
}
