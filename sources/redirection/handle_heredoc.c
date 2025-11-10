/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:52 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/10 12:53:59 by owhearn       ########   odam.nl         */
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

int	putstr_hd(char *line, int *fd)
{
	int	idx;

	idx = 0;
	while (line[idx] && line[idx] != '$')
		idx++;
	write(*fd, line, idx);
	return (idx);
}

int	set_heredoc_var(char *line, int *fd)
{
	int	idx;

	idx = 0;
	return (idx);
}

/*turns out this is not required, so it will no longer be worked on.*/
int	simplified_expansion(t_data *data, char *line, int *fd)
{
	int	idx;

	idx = 0;
	(void)data;
	// while (line[idx])
	// {
	// 	idx += putstr_hd(&line[idx], fd);
	// 	if (line[idx] && line[idx] == '$')
	// 		idx += set_heredoc_var(&line[idx], fd);
	// }
	ft_putendl_fd(line, *fd);
	return (0);
}

int	scan_line(char *line, char *delim, bool	quotes)
{
	int	size;

	size = ft_strlen(delim);
	if (ft_strlen(line) != size)
		return (0);
	if (!ft_strncmp(line, delim, size))
		return (1);
	return (0);
}

int	fill_heredoc(t_data *data, t_files *list, int *fd)
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
		if (list->quoted == false)
			ft_putendl_fd(line, *fd);
		else
			simplified_expansion(data, line, fd);
		ft_free(&line);
	}
	ft_free(&line);
	return (0);
}

int	handle_heredoc(t_data *data, t_files *list, int *fd)
{
	if (close_existing_fd_in(list, fd))
		return (1);
	if (create_hd_file(list, fd))
		return (1);
	if (fill_heredoc(data, list, fd))
		return (1);
	if (close(fd))
		print_close_fd_error();
	*fd = -1;
	*fd = open(list->filename, O_RDONLY);
	if (*fd == -1)
		return (infile_open_error(list));
	list->open = true;
	return (0);
}
