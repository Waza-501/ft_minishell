/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_append.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:49 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/31 14:24:55 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_append(t_data *data, t_commands *list, t_lexer *node)
{
	if (close_existing_fd_out(data, list))
		return (false);
	list->outfile_s = ft_strdup(node->string);
	if (!list->outfile_s)
		return (false);
	list->outfile = open(list->outfile_s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (list->outfile == -1)
		return (false);
	return (true);
}
