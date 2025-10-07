/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_output.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:55 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/07 15:04:03 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	close_existing_fd(t_commands *list)
// {
// 	if (list->infile == -1 || !list->infile_s)
// 		return (0);
// 	ft_free(list->infile_s);
// 	if (close(list->infile))
// 		return (1);
// 	list->infile = -1;
// 	return (0);
// }

bool	handle_output(t_commands *list, t_lexer *node)
{
	if (close_existing_fd(list))
		return (false);
	list->outfile_s = ft_strdup(node->string);
	if (!list->outfile_s)
		return (false);
	list->outfile = open(list->outfile_s, O_RDONLY);
	if (list->outfile == -1)
		return (false);
	return (true);
}
