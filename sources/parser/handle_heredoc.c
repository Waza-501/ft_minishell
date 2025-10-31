/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:52 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/31 14:25:27 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_hd_file(t_commands *list)
{
	char		*filenumber;
	static int	i = 0;

	filenumber = ft_itoa(i++);
	if (!filenumber)
		return (1);
	list->infile_s = ft_strjoin("/tmp/heredoc_", filenumber);
	ft_free(&filenumber);
	if (!list->infile_s)
		return (1);
	list->infile = open(list->infile_s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (list->infile == -1)
		return (1);
	list->hd = true;
	return (0);
}

bool	handle_heredoc(t_data *data, t_commands *list, t_lexer *node)
{
	(void)node;
	if (close_existing_fd_in(data, list))
		return (false);
	if (create_hd_file(list))
		return (false);
	return (true);
}
