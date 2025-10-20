/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:57 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/20 10:58:12 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_existing_fd_in(t_commands *list)
{
	if (list->infile == -1 || !list->infile_s)
		return (0);
	ft_free(list->infile_s);
	if (close(list->infile))
		return (1);
	list->infile = -1;
	return (0);
}

bool	handle_input(t_commands *list, t_lexer *node)
{
	if (close_existing_fd_in(list))
		return (false);
	list->infile_s = ft_strdup(node->string);
	if (!list->infile_s)
		return (false);
	list->infile = open(list->infile_s, O_RDONLY);
	if (list->infile == -1)
		return (false);
	return (true);
}
